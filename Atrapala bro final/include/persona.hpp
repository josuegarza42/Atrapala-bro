#ifndef PERSONA_HPP
#define PERSONA_HPP
#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "vertex.hpp"
#include "face.hpp"
#include "object.hpp"
#include "Transform.hpp"
using namespace std;

class Persona{
	public:
	Object player_obj;
	float tx,ty,tz;
	float sx,sy,sz;
	float rx,ry,rz;
	
	void translate(float tx, float ty, float tz);
	void rotate(float rx, float ry, float rz);
	void scale(float sx, float sy, float sz);
	
	Persona();
	void creaPlayer();
	void dibujaPlayer();
	void transformaPlayer(bool translate, bool scale);
};
#endif
