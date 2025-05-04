#include "SCOP_File.hpp"

int main(int argc, UNUSED char **argv)
{
	if (argc != 2)
		return (1);
	std::ifstream	file(argv[1]);

	if (!file.is_open())
		return (1);
	std::string	line;
	while (std::getline(file, line)){
		if (!parseLine(line))
			break ;
	}
}
