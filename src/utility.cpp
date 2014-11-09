#include "utility.h"

std::streamsize stream_size(std::ifstream *input) {
	input->seekg(0, std::ios::end);
	std::streamsize size = input->tellg();
	input->seekg(0, std::ios::beg);
	return size;
}