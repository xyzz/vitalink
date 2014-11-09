#include "elf.h"

#include <cstring>
#include <fstream>
#include <stdexcept>
#include <utility>

#include <iostream>

#include "elftypes.h"
#include "vitastructs.h"
#include "utility.h"

static const char ElfMagic[] = { 0x7f, 'E', 'L', 'F', '\0' };

Elf::Elf(std::vector<char> buf_):
	buf(std::move(buf_)) 
{
	Initialize();
}

Elf::Elf(const std::string &path) {
	std::ifstream input(path.c_str(), std::ios::in | std::ios::binary);
	if (!input)
		throw std::runtime_error("Cannot open input file for reading.");

	std::streamsize size = stream_size(&input);
	buf.resize(size);
	if (!input.read(buf.data(), size))
		throw std::runtime_error("Cannot read file into memory.");

	Initialize();
}

void Elf::Initialize() {
	header = reinterpret_cast<Elf32_Ehdr*>(&buf[0]);
	if (buf.size() < sizeof(*header))
		throw std::runtime_error("Cannot read ELF header");

	if (memcmp(header->e_ident, ElfMagic, std::strlen(ElfMagic)) != 0)
		throw std::runtime_error("Not an ELF file");

	if (buf.size() < header->e_phoff + sizeof(Elf32_Phdr) * header->e_phnum)
		throw std::runtime_error("Cannot read program headers");
	pheader = reinterpret_cast<Elf32_Phdr*>(&buf[header->e_phoff]);

	if (buf.size() < header->e_shoff + sizeof(Elf32_Shdr) * header->e_shnum)
		throw std::runtime_error("Cannot read sections table");

	sections = reinterpret_cast<Elf32_Shdr*>(&buf[header->e_shoff]);

	if (header->e_shstrndx >= header->e_shnum)
		throw std::runtime_error("Invalid index of section header table");

	shstr = &sections[header->e_shstrndx];
	if (buf.size() < shstr->sh_offset + shstr->sh_size)
		throw std::runtime_error("Cannot read .shstrtab");

	shstrtab = &buf[shstr->sh_offset];
}

void Elf::GetUndefinedSymbols(std::set<std::string> *output) {
	const Elf32_Shdr *symtab_hdr = nullptr;
	for (int i = 1; i < header->e_shnum; ++i) {
		if (sections[i].sh_type == SHT_SYMTAB) {
			symtab_hdr = &sections[i];
			break;
		}
	}

	if (!symtab_hdr)
		throw std::runtime_error("Cannot find .symtab section");

	if (symtab_hdr->sh_offset + symtab_hdr->sh_size >= buf.size())
		throw std::runtime_error("Cannot read .symtab section");

	if (symtab_hdr->sh_link >= header->e_shnum)
		throw std::runtime_error("Cannot find STRTAB for .symtab section");

	const Elf32_Shdr *strtab_hdr = &sections[symtab_hdr->sh_link];
	if (strtab_hdr->sh_offset + strtab_hdr->sh_size >= buf.size())
		throw std::runtime_error("Cannot read STRTAB section for .symtab");

	const char *strtab = &buf[strtab_hdr->sh_offset];
	const Elf32_Sym *symtab = reinterpret_cast<const Elf32_Sym*>(&buf[symtab_hdr->sh_offset]);
	for (int i = 1; i < symtab_hdr->sh_size / symtab_hdr->sh_entsize; ++i) {
		const Elf32_Sym &symbol = symtab[i];
		if (symbol.st_name >= strtab_hdr->sh_size)
			continue; // is it even a good idea to continue processing such broken elf?

		if (symbol.getType() == STT_NOTYPE && symbol.st_shndx == STN_UNDEF)
			output->insert(strtab + symbol.st_name);
	}
}

void Elf::FixupTopEnd() {
	uint32_t ent_top, ent_end, stub_top, stub_end;
	ent_top = ent_end = stub_top = stub_end = 0;

	if (header->e_phoff < 1)
		throw std::runtime_error("No segments defined");

	uint32_t base_vaddr = pheader[0].p_vaddr;
	int module_info_idx = 0;

	for (int i = 1; i < header->e_shnum; ++i) {
		auto &section = sections[i];
		if (section.sh_name >= shstr->sh_size)
			throw std::runtime_error("Cannot read name for section " + std::to_string(i));
		char *name = &shstrtab[section.sh_name];
		if (name == std::string(".sceLib.ent")) {
			ent_top = section.sh_addr - base_vaddr;
			ent_end = section.sh_addr + section.sh_size - base_vaddr;
		} else if (name == std::string(".sceLib.stub")) {
			stub_top = section.sh_addr - base_vaddr;
			stub_end = section.sh_addr + section.sh_size - base_vaddr;
		} else if (name == std::string(".sceModuleInfo.rodata")) {
			module_info_idx = i;
		}
	}
	if (!ent_top || !ent_end || !stub_top || !stub_end || !module_info_idx)
		throw std::runtime_error("Cannot fixup elf because some sections are missing");

	auto &module_info_hdr = sections[module_info_idx];
	if (module_info_hdr.sh_offset + module_info_hdr.sh_size >= buf.size())
		throw std::runtime_error("Cannot locate .sceModuleInfo.rodata");

	module_info *mi = reinterpret_cast<module_info*>(&buf[module_info_hdr.sh_offset]);
	mi->ent_top = ent_top;
	mi->ent_end = ent_end;
	mi->stub_top = stub_top;
	mi->stub_end = stub_end;
}

void Elf::Write(const std::string &path) {
	std::ofstream output(path.c_str(), std::ios::out | std::ios::binary);
	output.write(buf.data(), buf.size());
}
