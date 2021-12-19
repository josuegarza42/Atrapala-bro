#include "face.hpp"

Face::Face(){
}

Face::Face(vector <Hbox> Hboxslista){
	Hboxs=Hboxslista;
}

void Face::CalculaNormal(vector <Vertex> vertices){
	Vertex v1 = vertices[(Hboxs[0].vi)-1];
	Vertex v2 = vertices[(Hboxs[0].vf)-1];
	Vertex v3 = vertices[(Hboxs[1].vf)-1];
	
	arma::frowvec v1p ={v1.x,v1.y,v1.z}; 
	arma::frowvec v2p ={v2.x,v2.y,v2.z};
	arma::frowvec v3p ={v3.x,v3.y,v3.z};
	
	arma::frowvec NF = arma::cross(v2p-v1p, v3p-v1p);
	A= NF[0];
	B= NF[1];
	C= NF[2];
	D= -((A*v2.x)+(B*v2.y)+(C*v2.z));
	cout << "Normal F: " << NF << endl;
}

void Face::imprimir(vector <Vertex> vl){
	cout << "f ";
	vector<int>:: iterator it_vectorindices = indices.begin();
	while(it_vectorindices != indices.end()){
		cout << *it_vectorindices << " ";
		it_vectorindices++;
	}
	cout << endl;
	for(int i=0; i < Hboxs.size();i++){
		Hboxs[i].imprimir(vl);
	}
}


