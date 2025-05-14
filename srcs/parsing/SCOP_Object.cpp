#include "SCOP_File.hpp"

SCOP_Object::SCOP_Object(){
	v.x = (float *)malloc(START_SIZE * sizeof(float));
	v.y = (float *)malloc(START_SIZE * sizeof(float));
	v.z = (float *)malloc(START_SIZE * sizeof(float));
	vn.x = (float *)malloc(START_SIZE * sizeof(float));
	vn.y = (float *)malloc(START_SIZE * sizeof(float));
	vn.z = (float *)malloc(START_SIZE * sizeof(float));
	vt.u = (float *)malloc(START_SIZE * sizeof(float));
	vt.v = (float *)malloc(START_SIZE * sizeof(float));
};

SCOP_Object::~SCOP_Object(){
	free(v.x);
	free(v.y);
	free(v.z);
	free(vn.x);
	free(vn.y);
	free(vn.z);
	free(vt.u);
	free(vt.v);
};
