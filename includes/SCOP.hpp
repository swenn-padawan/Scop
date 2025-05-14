#pragma once

# include "debug.hpp"
# include "macro.hpp"
# include "SCOP_File.hpp"
# include <cstdlib>
# include <sstream>
# include <stdexcept>


/*@brief: Codegen */

# define FUNC_NAME(x) parse##x
# define FUNC_PROTO(x) FUNC_NAME(x)(std::string line, SCOP_Object &obj)
	
#define PARSE_GEN_WT_ALLOC(NAME, LOG_FN)									\
	void FUNC_PROTO(NAME){													\
		UNUSED(obj);														\
		UNUSED(line);														\
		LOG_FN("In " #NAME ": %s", line.c_str());							\
	}																		\

#define PARSE_GEN_NAME(NAME, LOG_FN)								\
	void FUNC_PROTO(NAME){											\
		UNUSED(obj);												\
		UNUSED(line);												\
		std::string	id;												\
		std::stringstream ss(line);									\
		ss >> id;													\
		ss >> obj.name;												\
		LOG_FN("In " #NAME ": %s", line.c_str());					\
		LOG_FN("In parseName: %s", line.c_str());					\
	}																\

#define PARSE_GEN_VEC3(NAME, LOG_FN, FIELD)										\
	void FUNC_PROTO(NAME){														\
		UNUSED(obj);															\
		UNUSED(line);															\
		std::string	id;															\
		std::stringstream ss(line);												\
		static int	index = 0;													\
		ss >> id;																\
		LOG_FN("%s", line.c_str());												\
		ss >> obj.FIELD.x[index] >> obj.FIELD.y[index] >> obj.FIELD.z[index];	\
		LOG_FN("%s.x[%d] = %f | %s.y[%d] = %f | %s.z[%d] = %f",					\
			#FIELD, index, obj.FIELD.x[index],									\
			#FIELD, index, obj.FIELD.y[index],									\
			#FIELD, index, obj.FIELD.z[index]);									\
		index++;																\
	}																			\


#define PARSE_GEN_VEC2(NAME, LOG_FN, FIELD)					\
	void FUNC_PROTO(NAME){									\
		UNUSED(obj);										\
		UNUSED(line);										\
		std::string	id;										\
		std::stringstream ss(line);							\
		static int	index = 0;								\
		ss >> id;											\
		LOG_FN("%s", line.c_str());							\
		ss >> obj.FIELD.u[index] >> obj.FIELD.v[index];		\
		LOG_FN("%s.u[%d] = %f | %s.v[%d] = %f",				\
			#FIELD, index, obj.FIELD.u[index],              \
			#FIELD, index, obj.FIELD.v[index]);             \
		index++; \
	}\
