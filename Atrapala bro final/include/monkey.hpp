#ifndef MONKEY_HPP
#define MONKEY_HPP
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

class Monkey{
	public:
	Object monkey_obj;
	Object hit_boxM;
	int score;
	float tx,ty,tz;
	float sx,sy,sz;
	float rx,ry,rz;

	
	void translate(float, float, float);
	void rotate(float, float, float);
	void scale(float, float, float);
	
	Monkey();
	void creaMonkey();
	void dibujaMonkey();
	void transformaMonkey(bool translate, bool scale);
};
#endif
