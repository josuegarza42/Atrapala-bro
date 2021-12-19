#include "monkey.hpp"

Monkey:: Monkey(){
}

void Monkey:: creaMonkey(){
	monkey_obj.setnombre("modelos/monkey.obj");
	monkey_obj.read_obj();
	hit_boxM.setnombre("modelos/monkeyBox.obj");
	hit_boxM.read_obj();

	tx=0.0;
	ty=0.0;
	tz=0.0;
	rx=0.0;
	ry=0.0;
	rz=0.0;
	sx=1.0;
	sy=1.0;
	sz=1.0;
	
}

void Monkey:: dibujaMonkey(){

	vector <int> :: iterator iterador_indices;
	vector <Face> :: iterator iterador_caras;

	
	glColor3f(0.5, 0.25, 0.0);
	glBegin(GL_TRIANGLES);
	for(iterador_caras=monkey_obj.face_list.begin();iterador_caras!=monkey_obj.face_list.end();iterador_caras++){
		for(iterador_indices=iterador_caras->indices.begin();iterador_indices!= iterador_caras->indices.end();iterador_indices++){
			glVertex3f(monkey_obj.vertex_list[*iterador_indices-1].x,monkey_obj.vertex_list[*iterador_indices-1].y,monkey_obj.vertex_list[*iterador_indices-1].z);
		}
	}

	glEnd();
}

void Monkey:: transformaMonkey(bool translate, bool scale){
	Transform Tr= Transform();
	arma::fmat trans = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	
	if(translate == true){
		trans = trans * Tr.T(tx, ty, tz);
	}
	if(scale ==  true){
		trans = trans * Tr.S(sx,sy,sz);
	}	
	
	for ( unsigned int i=0; i<monkey_obj.vertex_list.size(); i++ ) {
		arma::fcolvec v = {{monkey_obj.vertex_list[i].x},{monkey_obj.vertex_list[i].y},{monkey_obj.vertex_list[i].z},{monkey_obj.vertex_list[i].w}};
		arma::fcolvec vp = trans * v;
		monkey_obj.vertex_list[i]={{vp[0]},{vp[1]},{vp[2]}};
	}
	for ( unsigned int i=0; i<hit_boxM.vertex_list.size(); i++ ) {
		arma::fcolvec va = {{hit_boxM.vertex_list[i].x},{hit_boxM.vertex_list[i].y},{hit_boxM.vertex_list[i].z},{hit_boxM.vertex_list[i].w}};
		arma::fcolvec vpa = trans * va;
		hit_boxM.vertex_list[i]={{vpa[0]},{vpa[1]},{vpa[2]}};
	}
}

void Monkey:: rotate(float rx, float ry, float rz){
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
}

void Monkey:: scale(float sx, float sy, float sz){
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}

void Monkey:: translate(float tx, float ty, float tz){
	this->tx = tx;
	this->ty = ty;
	this->tz = tz;
}
