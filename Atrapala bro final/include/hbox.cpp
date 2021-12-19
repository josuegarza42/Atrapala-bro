#include "hbox.hpp"

Hbox::Hbox(){
	t=0;
	dt=0.001;
	tx=0.0;
	ty=0.0;
	tz=0.0;
	sx=1.0;
	sy=1.0;
	sz=1.0;
	Max=9;
}

Hbox::Hbox(int va, int vb){
	vi=va;
	vf=vb;
}
/*
void Hbox:: dibujaHbox(){

	vector <int> :: iterator iterador_indices2;
	vector <Face> :: iterator iterador_caras2;
	
	glColor3f(0.5, 0.5, 1.0);
	glBegin(GL_TRIANGLES);
	for(iterador_caras2=hit_box.face_list.begin();iterador_caras2!=hit_box.face_list.end();iterador_caras2++){
		for(iterador_indices2=iterador_caras2->indices.begin();iterador_indices2!= iterador_caras2->indices.end();iterador_indices2++){
			glVertex3f(hit_box.vertex_list[*iterador_indices2-1].x,hit_box.vertex_list[*iterador_indices2-1].y,hit_box.vertex_list[*iterador_indices2-1].z);
		}
	}

	glEnd();
}*/

void Hbox::imprimir(vector <Vertex> hl){

	cout<< "\t\t hi:"<<vi<<endl; hl[vi-1].imprimir();
	cout<< "\t\t hf:"<<vf<<endl; hl[vf-1].imprimir();
}

void Hbox:: scale(float sx, float sy, float sz){
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}

void Hbox:: translate(float tx, float ty, float tz){
	this->tx = tx;
	this->ty = ty;
	this->tz = tz;
}


