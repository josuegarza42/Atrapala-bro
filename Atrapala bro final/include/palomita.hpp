#ifndef PALOMITA_HPP
#define PALOMITA_HPP
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "vertex.hpp"
#include "face.hpp"
#include "object.hpp"
#include "Transform.hpp"
using namespace std;

class Palomita{
	public:
	Object palomita_obj;
	Object hit_box;
	arma:: frowvec QtAux;
	arma::frowvec P1,P2,P3,P4;
	vector <Vertex> copia,copiab;
	float tx,ty,tz;
	float sx,sy,sz;
	float t;
	float dt;
	int Max;
	
	void translate(float, float, float);
	void scale(float, float, float);
	
	
	Palomita();
	void creaPalomita();
	void ajustaCoordenadas();
	void dibujaPalomita();
	void transformaPalomita(bool translate, bool scale);
	void Bezier();
	void regresa();
};
#endif
