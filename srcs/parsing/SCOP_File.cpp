
#include "SCOP_File.hpp"

SCOP_File::SCOP_File():data(nullptr), size(0){}

SCOP_File::SCOP_File(const char* filepath) {
	std::ifstream	file(filepath);

	if (!file.is_open()){
		std::cerr << "SCOP: Error: Failed to open: " << filepath << std::endl;
		return ;
	}
}

SCOP_File::~SCOP_File() {}


size_t SCOP_File::getSize(){
    return size;
}
