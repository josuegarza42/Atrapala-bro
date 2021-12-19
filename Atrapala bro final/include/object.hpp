#ifndef OBJECT_HPP
#define OBJECT_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <armadillo>
#include <vector>
#include "vertex.hpp"
#include "hbox.hpp"
#include "face.hpp"
using namespace std;


class Object{
	public:
		string obj_file;
		string obj_name;
		vector <Hbox> Hbox_list;
		vector <Vertex> vertex_list;
		vector <Face> face_list;
		
		Object();
		void read_obj();
		void print_obj();
		void setnombre(const char *nombre);
};
#endif
