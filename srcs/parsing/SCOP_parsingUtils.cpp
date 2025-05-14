#include "SCOP.hpp"
#include "SCOP_File.hpp"
#include "debug.hpp"
#include "macro.hpp"
#include <cstdlib>
#include <sstream>
#include <stdexcept>

typedef void (*parseFuncs)(std::string line,  SCOP_Object &obj);

void	parseSkip(std::string line, SCOP_Object &object){
	UNUSED(object);
	UNUSED(line);
	SCOP_WARN("In parseSkip: %s", line.c_str());
}

void	parseName(std::string line, SCOP_Object &obj){
	
	std::string			id;
	std::stringstream	ss(line);

	ss >> id;
	ss >> obj.name;
	SCOP_LOG("In parseName: %s", line.c_str());
	SCOP_LOG("Name: %s", obj.name.c_str());
}

void	parseVertex(std::string line, SCOP_Object &obj){
	UNUSED(obj);
	UNUSED(line);
	SCOP_LOG("In parseVertex: %s", line.c_str());

	std::string			id;
	std::stringstream	ss(line);
	static int			index = 0;

	ss >> id;
	ss >> obj.v.x[index] >> obj.v.y[index] >> obj.v.z[index];
	SCOP_LOG("v.x[%d] = %f | v.y[%d] = %f | v.z[%d] = %f", index, obj.v.x[index], index, obj.v.y[index], index, obj.v.z[index]);
}

void	parseNormals(std::string line, SCOP_Object &obj){
	UNUSED(obj);
	UNUSED(line);
	SCOP_LOG("In parseNormals: %s", line.c_str());
	
	std::string			id;
	std::stringstream	ss(line);
	static int			index = 0;

	ss >> id;
	ss >> obj.vn.x[index] >> obj.vn.y[index] >> obj.vn.z[index];
	SCOP_LOG("vn.x[%d] = %f | vn.y[%d] = %f | vn.z[%d] = %f", index, obj.vn.x[index], index, obj.vn.y[index], index, obj.vn.z[index]);
}

void	parseTextures(std::string line, SCOP_Object &obj){
	UNUSED(obj);
	UNUSED(line);
	SCOP_LOG("In parseTextures: %s", line.c_str());

	std::string			id;
	std::stringstream	ss(line);
	static int			index = 0;

	ss >> id;
	ss >> obj.vt.u[index] >> obj.vt.v[index];
	SCOP_LOG("vt.u[%d] = %f | vt.v[%d] = %f", index, obj.vt.u[index], index, obj.vt.v[index]);
}

void	parseError(std::string line, SCOP_Object &obj){
	UNUSED(obj);
	UNUSED(line);
	SCOP_ERR("In parseError: %s", line.c_str());
}

parseFuncs	getParseFuncs(std::string line){
	std::stringstream	ss(line);
	std::string			type;

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
	if (type == "vt")
		return (&parseTextures);
	return (&parseError);
}

bool	parseLine(std::string line){
	parseFuncs	funcPtr;
	SCOP_Object	obj;

	funcPtr = getParseFuncs(line);
	try{
		funcPtr(line, obj);
	}catch(std::exception& e){
		SCOP_ERR("%s", e.what());
		return (false);
	}
	return (true);
}
