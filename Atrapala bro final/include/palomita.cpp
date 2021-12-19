#include "palomita.hpp"

Palomita:: Palomita(){

	t=0;
	dt=0.009;
	tx=0.0;
	ty=0.0;
	tz=0.0;
	sx=1.0;
	sy=1.0;
	sz=1.0;
	Max=9;
}
void Palomita:: ajustaCoordenadas(){
	
	srand (time(NULL));
	float x1= (float) ((int)rand()%((Max-1)*(int)pow(10,2))/pow(10,2)+1);
	//cout<<x1<<endl;
	
	P1 = {palomita_obj.vertex_list[(palomita_obj.vertex_list.size())/2].x,palomita_obj.vertex_list[(palomita_obj.vertex_list.size())/2].y,palomita_obj.vertex_list[(palomita_obj.vertex_list.size())/2].z};
	P2 = {P1[0]+10,P1[1]+5,P1[2]};
	P4 = {x1,0,0};
	P3 = {x1,P4[1]+10,0};
}
void Palomita:: creaPalomita(){
	palomita_obj.setnombre("modelos/palomita.obj");
	palomita_obj.read_obj();
	hit_box.setnombre("modelos/palomitaBox.obj");
	hit_box.read_obj();
}

void Palomita:: dibujaPalomita(){

	vector <int> :: iterator iterador_indices;
	vector <Face> :: iterator iterador_caras;

	
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);
	for(iterador_caras=palomita_obj.face_list.begin();iterador_caras!=palomita_obj.face_list.end();iterador_caras++){
		for(iterador_indices=iterador_caras->indices.begin();iterador_indices!= iterador_caras->indices.end();iterador_indices++){
			glVertex3f(palomita_obj.vertex_list[*iterador_indices-1].x,palomita_obj.vertex_list[*iterador_indices-1].y,palomita_obj.vertex_list[*iterador_indices-1].z);
		}
	}

	glEnd();
}

void Palomita::Bezier(){
	arma::fmat MB= {{-1,3,-3,1},{3,-6,3,0},{-3,3,0,0},{1,0,0,0}};
	arma:: fmat GB (4,3);
	GB.row(0)=P1;
	GB.row(1)=P2;
	GB.row(2)=P3;
	GB.row(3)=P4;
	
	if(t==0){
		arma:: frowvec T={powf(t,3),powf(t,2),t,1};
		arma:: frowvec Qt = T * MB *GB;
		QtAux= Qt;
		//cout<<QtAux<<endl;
	}
	if(t<=1){
		arma:: frowvec T={powf(t,3),powf(t,2),t,1};
		arma:: frowvec Qt = T * MB *GB;
		//cout<<"Qt: "<<Qt<<endl;
		arma:: frowvec D= Qt-QtAux;
		//cout<<"D: "<<D<<endl;
		translate(D[0],D[1],D[2]);
		transformaPalomita(true,false);
		dibujaPalomita();
		QtAux=Qt;
		t= t+dt;
	}
	else{
		if(t>1){
			regresa();
		}
	}
}

void Palomita:: regresa(){
	t=0;
	palomita_obj.vertex_list=copia;
	hit_box.vertex_list=copiab;
	ajustaCoordenadas();
}

void Palomita:: scale(float sx, float sy, float sz){
	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
}

void Palomita:: translate(float tx, float ty, float tz){
	this->tx = tx;
	this->ty = ty;
	this->tz = tz;
}

void Palomita:: transformaPalomita(bool translate, bool scale){
	Transform Tr= Transform();
	arma::fmat trans = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	
	if(translate == true){
		trans = trans * Tr.T(tx, ty, tz);
	}
	if(scale ==  true){
		trans = trans * Tr.S(sx,sy,sz);
	}	
	
	for ( unsigned int i=0; i<palomita_obj.vertex_list.size(); i++ ) {
		arma::fcolvec v = {{palomita_obj.vertex_list[i].x},{palomita_obj.vertex_list[i].y},{palomita_obj.vertex_list[i].z},{palomita_obj.vertex_list[i].w}};
		arma::fcolvec vp = trans * v;
		palomita_obj.vertex_list[i]={{vp[0]},{vp[1]},{vp[2]}};
	}
	for ( unsigned int i=0; i<hit_box.vertex_list.size(); i++ ) {
		arma::fcolvec va = {{hit_box.vertex_list[i].x},{hit_box.vertex_list[i].y},{hit_box.vertex_list[i].z},{hit_box.vertex_list[i].w}};
		arma::fcolvec vpa = trans * va;
		hit_box.vertex_list[i]={{vpa[0]},{vpa[1]},{vpa[2]}};
	}
}

