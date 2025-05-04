#include "SCOP_File.hpp"
#include <sstream>
#include <stdexcept>

typedef void (*parseFuncs)(std::string line, UNUSED SCOP_Object &object);

void	parseError(UNUSED std::string line, UNUSED SCOP_Object &object){
	throw std::runtime_error("SCOP: Error: Unknown Id");
}

void	parseVertex(UNUSED std::string line, UNUSED SCOP_Object &object){	
	std::cout << "In parseVertex" << std::endl;
	static int	index = 0;
	std::stringstream	ss(line);
	std::string	type;

	ss >> type;
	ss >> object.v.x[index] >> object.v.y[index] >> object.v.z[index];
	index++;
}

void	parseSkip(UNUSED std::string line, UNUSED SCOP_Object &object){
	std::cout << "In parseSkip" << std::endl;
}

void	parseName(UNUSED std::string line, UNUSED SCOP_Object &object){
	std::cout << "In parseName" << std::endl;
	std::string			type;
	std::stringstream	ss(line);

	ss >> type;
	ss >> object.name;
}

void	parseNormals(UNUSED std::string line, UNUSED SCOP_Object &object){
	std::cout << "In parseNormals" << std::endl;
	static int	index = 0;
	std::stringstream	ss(line);
	std::string	type;

	ss >> type;
	ss >> object.vn.x[index] >> object.vn.y[index] >> object.vn.z[index];
	index++;
}

parseFuncs	getParseFuncs(std::string line){
	std::stringstream ss(line);
	std::string	type;

	ss >> type;
	if (type == "#")
		return (&parseSkip);
	if (type == "mtllib")
		return (&parseSkip);
	if (type == "o")
		return (&parseName);
	if (type == "v")
		return (&parseVertex);
	if (type == "vn")
		return (&parseNormals);
	return (&parseError);
}

bool	parseLine(std::string line){
	parseFuncs	funcPtr;
	SCOP_Object	obj;

	funcPtr = getParseFuncs(line);
	try{
		funcPtr(line, obj);
	}catch(std::exception& e){
		std::cout << e.what() << std::endl;
		return (false);
	}
	return (true);
}
