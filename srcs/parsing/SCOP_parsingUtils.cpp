#include "SCOP.hpp"
#include "debug.hpp"
#include "macro.hpp"

typedef void (*parseFuncs)(std::string line,  SCOP_Object &obj);


PARSE_GEN_WT_ALLOC(Skip, SCOP_WARN);

PARSE_GEN_WT_ALLOC(Error, SCOP_ERR);

PARSE_GEN_NAME(Name, SCOP_LOG);

PARSE_GEN_VEC3(Vertex, SCOP_LOG, v);

PARSE_GEN_VEC3(Normals, SCOP_LOG, vn);

PARSE_GEN_VEC2(Textures, SCOP_LOG, vt);

parseFuncs	getParseFuncs(std::string line){
	std::stringstream	ss(line);
	std::string			type;

	ss >> type;
	if (type == "#")
		return (FUNC_NAME(Skip));
	if (type == "mtllib")
		return (FUNC_NAME(Skip));
	if (type == "o")
		return (FUNC_NAME(Name));
	if (type == "v")
		return (FUNC_NAME(Vertex));
	if (type == "vn")
		return (FUNC_NAME(Normals));
	if (type == "vt")
		return (FUNC_NAME(Textures));
	return (FUNC_NAME(Error));
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
