#include "vertex.hpp"

Vertex::Vertex(){
	x = y = z = 0.0f;
	w=1.0;
}
Vertex::Vertex(float xi, float yi, float zi){
	x = xi;
	y = yi;
	z = zi;
	w= 1.0;
}
void Vertex::imprimir(){
	cout << "x=" << x << "y=" << y << "z=" << z << endl;
}

