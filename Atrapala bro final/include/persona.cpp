#include "persona.hpp"

Persona:: Persona(){
}

void Persona:: creaPlayer(){
	player_obj.setnombre("modelos/persona.obj");
	player_obj.read_obj();
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

void Persona:: dibujaPlayer(){
	
	vector <int> :: iterator iterador_indices;
	vector <Face> :: iterator iterador_caras;
	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for(iterador_caras=player_obj.face_list.begin();iterador_caras!=player_obj.face_list.end();iterador_caras++){
		for(iterador_indices=iterador_caras->indices.begin();iterador_indices!= iterador_caras->indices.end();iterador_indices++){
			glVertex3f(player_obj.vertex_list[*iterador_indices-1].x,player_obj.vertex_list[*iterador_indices-1].y,player_obj.vertex_list[*iterador_indices-1].z);
		}
	}
	glEnd();
}

void Persona:: transformaPlayer(bool translate, bool scale){
	
	Transform Tr= Transform();
	arma::fmat trans = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	 
	if(translate == true){
		trans = trans * Tr.T(tx, ty, tz);
	}
	if(scale ==  true){
		trans = trans * Tr.S(sx,sy,sz);
	}	
	
	for ( unsigned int i=0; i<player_obj.vertex_list.size(); i++ ) {
		arma::fcolvec v = {{player_obj.vertex_list[i].x},{player_obj.vertex_list[i].y},{player_obj.vertex_list[i].z},{player_obj.vertex_list[i].w}};
		arma::fcolvec vp = trans * v;
		player_obj.vertex_list[i]={{vp[0]},{vp[1]},{vp[2]}};
	}
}

void Persona:: rotate(float rx, float ry, float rz){
	this->rx = rx;
	this->ry = ry;
	this->rz = rz;
}

void Persona:: scale(float sx, float sy, float sz){
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}

void Persona:: translate(float tx, float ty, float tz){
	this->tx = tx;
	this->ty = ty;
	this->tz = tz;
}
