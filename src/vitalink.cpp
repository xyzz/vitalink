#include <iostream>
#include <stdexcept>

#include "elf.h"
#include "stubs.h"

void fixup_elf(int argc, char *argv[]) {
	try {
		Elf elf(argv[2]);
		elf.FixupTopEnd();
		elf.Write(argv[2]);
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

void generate_stubs(int argc, char *argv[]) {
	for (int i = 2; i < argc; ++i)
		process_file(argv[i]);

	try {
		load_nids(argv[1]);
	} catch (const std::runtime_error &e) {
		std::cerr << argv[2] << ": " << e.what() << std::endl;
		exit(1);
	}

	output_stubs("__stubs.S");
}

void print_usage() {
	std::cout << "Usage: vitalink NIDS.xml object.o..." << std::endl;
	std::cout << "       vitalink --fixup homebrew.elf" << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		print_usage();
		return 1;
	}

	if (argv[1] == std::string("--fixup"))
		fixup_elf(argc, argv);
	else
		generate_stubs(argc, argv);

	return 0;
}
