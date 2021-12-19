#ifndef HBOX_HPP
#define HBOX_HPP
#include <iostream>
#include "vertex.hpp"
using namespace std;

class Hbox{
public:
	int vi;
	int vf;
	float tx,ty,tz;
	float sx,sy,sz;
	float t;
	float dt;
	int Max;
	Hbox();
	//Object hit_box;
	Hbox(int va, int vb);
	void imprimir(vector <Vertex> hl);
	void translate(float, float, float);
	void scale(float, float, float);
	//void dibujaHbox();
};
#endif
