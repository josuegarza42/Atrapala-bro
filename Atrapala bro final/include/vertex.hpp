#ifndef VERTEX_HPP
#define VERTEX_HPP
#include <iostream>
#include <armadillo>
using namespace std;

class Vertex{
public:	
	float x;
	float y;
	float z;
	float w;
	Vertex();
	Vertex(float xi, float yi, float zi);
	void imprimir();
};
#endif
