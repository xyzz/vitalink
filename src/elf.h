#pragma once

#include <set>
#include <string>
#include <vector>

#include "elftypes.h"

class Elf {
public:
	explicit Elf(std::vector<char> buf_);
	explicit Elf(const std::string &path);
	void GetUndefinedSymbols(std::set<std::string> *output);
	void FixupTopEnd();
	void Write(const std::string &path);
private:
	void Initialize();
	std::vector<char> buf;
	Elf32_Ehdr *header;
	Elf32_Phdr *pheader;
	Elf32_Shdr *sections;
	Elf32_Shdr *shstr;
	char *shstrtab;
};
