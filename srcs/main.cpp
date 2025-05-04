#include "parsing.hpp"

int main(int argc, UNUSED char **argv)
{
	if (argc != 2)
		return (1);
	SCOP_MapFile file;

	try {
	file = SCOP_MapFile(argv[1]);
	}catch (const std::runtime_error& e){
		std::cerr << "SCOP Parse Error: " << e.what() << std::endl;
		return (1);
	}

	std::cout.write(static_cast<char *>(file.getData()), file.getSize());
}
