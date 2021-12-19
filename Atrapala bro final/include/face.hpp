#ifndef FACE_HPP
#define FACE_HPP
#include <iostream>
#include <vector>
#include <armadillo>
#include "vertex.hpp"
#include "hbox.hpp"
using namespace std;

class Face{
public:
	vector <Hbox> Hboxs; 
	vector <int> indices;
	Face();
	vector <Vertex> vertex_list_faces;
	Face(vector <Hbox> Hboxslista);
	float A,B,C,D;
	
	void CalculaNormal(vector <Vertex> vertices);
	void imprimir(vector<Vertex>);
};
#endif
