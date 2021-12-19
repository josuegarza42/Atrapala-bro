#include "object.hpp"

Object:: Object(){
}

void Object::setnombre(const char *file){
	obj_file=file;
}

void Object::read_obj(){
	string linea;
	ifstream archivoOBJ(obj_file);
	
	while(getline (archivoOBJ, linea)){
		if(linea.size()>1){
			if((linea[0] == 'o' || linea[0] == 'g')){
				string name =linea.substr(2);
				obj_name= name;
			}
			if(linea[0] == 'v' && linea[1] != 'n'){
				string numeros;
				numeros= linea.substr(2);
				stringstream num_segmentados;
				num_segmentados<< numeros;
				float x,y,z;
				num_segmentados>> x >> y >> z;
				Vertex v= Vertex(x,y,z);
				vertex_list.push_back(v);
			}
			
			if(linea[0] == 'f'){
				Face f;
				vector <int> :: iterator it;
				int vert;
				int prev_vert2= -1;
				int prev_vert= -1;
				string aux_string;
				string nums;
				nums=linea.substr(2);
				stringstream num_seg;
				//stringstream num_seg_aux;
				num_seg<<nums;
				while(!num_seg.eof()){
					num_seg>> vert;
					if(prev_vert != vert){
						prev_vert = vert;
						f.indices.push_back(vert);
					}
					num_seg>>aux_string;
					if(aux_string[0]!= '/'){
						stringstream num_seg_aux;
						num_seg_aux << aux_string;
						num_seg_aux >> vert;
						if(prev_vert != vert && prev_vert2 != vert){
							prev_vert2 = vert;
							prev_vert = vert;
							f.indices.push_back(vert);
						}
					}
				}
				it = f.indices.begin();
 				int prev = *it;
				it++;
				for(;it != f.indices.end();++it){
					int v = *it;
					Hbox hb = Hbox(prev,v);
					Hbox_list.push_back(hb);
					f.Hboxs.push_back(hb);
					prev = v;
				}
				Hbox hb= Hbox(f.indices[f.indices.size()-1],f.indices[0]);
				f.Hboxs.push_back(hb);
				Hbox_list.push_back(hb);
				face_list.push_back(f);
			}
		}
			
	}
	archivoOBJ.close();
}

void Object::print_obj(){
	string prob = obj_file;
	prob=prob.substr(7);
	if(obj_name == "surface"){
		
		cout << "NOMBRE DE ARCHIVO: "<< prob<<endl;
	}
	else{
		cout << "NOMBRE DE ARCHIVO: "<< obj_name<<endl;
	}
	for(int i=0; i<face_list.size();i++){
		face_list[i].imprimir(vertex_list);
		face_list[i].CalculaNormal(vertex_list);
	}
}
