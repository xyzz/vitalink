#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <set>
#include <vector>

#include "rapidxml.hpp"

#include "elf.h"
#include "utility.h"

std::set<std::string> g_undefined_symbols;

const std::string g_stubs_template = R"(
.macro STUB name
.global \name
\name:
MOV R0, #0xFFFFFFFF
BX LR
NOP
.endm

.code 32
)";

struct ImportedFunc {
	std::string name;
	uint32_t nid;

	ImportedFunc(std::string name_, uint32_t nid_):
		name(name_),
		nid(nid_)
	{}
};

struct Import {
	std::string name;
	uint32_t nid;
	std::vector<ImportedFunc> imported_funcs;

	Import(std::string name_, uint32_t nid_):
		name(name_),
		nid(nid_)
	{}
	Import() {}
};

std::map<uint32_t, Import> g_imports;

void load_nids(char *path) {
	std::ifstream input(path, std::ios::in);
	if (!input)
		throw std::runtime_error(std::string("Cannot open ") + path + " for reading");

	std::streamsize size = stream_size(&input);
	std::vector<char> text(size + 1);
	if (!input.read(text.data(), size))
		throw std::runtime_error(std::string("Cannot read ") + path);

	rapidxml::xml_document<> doc;
	doc.parse<0>(text.data());
	for (auto library = doc.first_node(); library; library = library->next_sibling())
		for (auto module = library->first_node(); module; module = module->next_sibling()) {
			std::string module_name = module->first_attribute("name")->value();
			std::string module_nid_str = module->first_attribute("nid")->value();
			uint32_t module_nid = strtoul(module_nid_str.substr(2).c_str(), NULL, 16);

			for (auto atom = module->first_node(); atom; atom = atom->next_sibling()) {
				if (atom->name() == std::string("func")) {
					std::string name = atom->first_attribute("name")->value();
					std::string nid_str = atom->first_attribute("nid")->value();
					uint32_t nid = strtoul(nid_str.substr(2).c_str(), NULL, 16);

					if (g_undefined_symbols.count(name)) {
						if (!g_imports.count(module_nid))
							g_imports[module_nid] = Import(module_name, module_nid);
						g_imports[module_nid].imported_funcs.push_back(ImportedFunc(name, nid));
					}
				}
			}
		}
}

void output_stubs(const char *path) {
	std::ofstream output(path, std::ios::out);
	output << g_stubs_template << std::endl;

	for (auto &i : g_imports)
		for (auto &function : i.second.imported_funcs)
			output << "STUB " << function.name << std::endl;

	output << std::endl << ".section .sceImport.rodata, \"a\"" << std::endl;
	for (auto &i : g_imports) {
		auto &module = i.second;
		output << module.name << "_name: .string \"" << module.name << "\"" << std::endl;
	}

	output << std::endl << ".section .sceFNID.rodata, \"a\"" << std::endl;
	for (auto &i : g_imports) {
		auto &module = i.second;
		output << module.name << "_nids: ";
		for (auto &func : module.imported_funcs)
			output << ".word 0x" << std::hex << func.nid << "; ";
		output << std::endl;
	}

	output << std::endl << ".section .sceFStub.rodata, \"a\"" << std::endl;
	for (auto &i : g_imports) {
		auto &module = i.second;
		output << module.name << "_funcs: ";
		for (auto &func : module.imported_funcs)
			output << ".word " << func.name << "; ";
		output << std::endl;
	}

	output << std::endl << ".section .sceLib.stub, \"a\"" << std::endl;
	for (auto &i : g_imports) {
		auto &module = i.second;
		output << ".hword 0x34; .hword 0; .hword 0; .hword " << module.imported_funcs.size() << "; .hword 0; .hword 0; "
			<< ".word 0; .word 0x" << std::hex << module.nid << "; .word " << module.name << "_name; "
			<< ".word 0; .word " << module.name << "_nids; .word " << module.name << "_funcs; "
			<< ".word 0; .word 0; .word 0; .word 0;" << std::endl;
	}

	output << std::endl << ".section .sceModuleInfo.rodata, \"a\"" << std::endl;
	output << ".hword 0x0; .hword 0x101; .string \"01234567890123456789012345\"; .byte 0x6; .word 0; "
		<< ".word 0; .word 0; .word 0; .word 0; .word 0; .word 0; .word 0; .word 0; "
		<< ".word module_start; .word 0; .word 0; .word 0; .word 0; .word 0;" << std::endl;

	output << std::endl << ".section .sceExport.rodata, \"a\"" << std::endl;
	output << "export_nids: .word 0x935CD196" << std::endl << 
		"export_funcs: .word module_start" << std::endl;

	output << std::endl << ".section .sceLib.ent, \"a\"" << std::endl;
	output << ".hword 0x20; .hword 0; .hword 0x8000; .hword 1; .word 0; .word 0; .word 0; "
		<< ".word 0; .word export_nids; .word export_funcs;" << std::endl;
}

void process_file(char *path) {
	try {
		Elf elf(path);
		elf.GetUndefinedSymbols(&g_undefined_symbols);
	} catch (const std::runtime_error &e) {
		std::cerr << path << ": " << e.what() << std::endl;
	}
}
