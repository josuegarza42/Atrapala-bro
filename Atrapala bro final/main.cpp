
#include <stdio.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "include/persona.hpp"
#include "include/monkey.hpp"
#include "include/palomita.hpp"
#include "include/hbox.hpp"
#include "include/face.hpp"
#include "include/object.hpp"
#include "include/Transform.hpp"

void key_callback(GLFWwindow* window,int ket,int scancode,int action,int mods);
void colision();
Monkey monkey = Monkey();
Palomita pal= Palomita();
Persona p1= Persona();
arma::frowvec eye = {0.0, 0.0, 10.0};
arma::frowvec camera = {0.0, 0.0, 0.0};
arma::frowvec va = {0.0, 1.0, 0.0};
int mood=0;

int main( void ){

	GLFWwindow* window;
	
	if( !glfwInit() ){
		fprintf( stderr, "Fallo al inicializar GLFW\n" );
		getchar();
		return -1;
	}
	window = glfwCreateWindow(800, 500, "Atrapala bro", NULL, NULL);
	if( window == NULL ) {
		fprintf( stderr, "Fallo al abrir la ventana de GLFW.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClearColor(0.0f, 0.0f, 7.0f, 2.0f);
	
//  Proyecciones
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	
//  Proyección en paralelo
	glViewport(0, 0, width, height);
	glOrtho(-10, 10, 0.0 , 10.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	p1.creaPlayer();
	p1.scale(0.9,0.9,0.9);
	p1.translate(-7.6,0,0);
	p1.rotate(0,0,0);
	p1.transformaPlayer(true,true);
	
	monkey.creaMonkey();
	monkey.scale(2.5,2.5,2.5);
	monkey.translate(1.0,0,0);
	monkey.rotate(0,0,0);
	monkey.transformaMonkey(true,true);
	
	
	pal.creaPalomita();
	pal.translate(-7.05,2.68,0);
	pal.transformaPalomita(true,false);
	pal.ajustaCoordenadas();
	pal.copia= pal.palomita_obj.vertex_list;
	pal.copiab=pal.hit_box.vertex_list;
	
	do {
		glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT );
		glMatrixMode(GL_MODELVIEW);
		glfwSetKeyCallback(window,key_callback);
		glLoadIdentity();
		gluLookAt(eye[0], eye[1], eye[2], camera[0], camera[1], camera[2], va[0],va[1] ,va[2]);
		
		
		monkey.dibujaMonkey();
		p1.dibujaPlayer();
		
		pal.Bezier();
		colision();
		
		glfwPollEvents();
		glFlush();
		glfwSwapBuffers(window);
		

		} while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

	glfwTerminate();

	return 0;
}
void key_callback(GLFWwindow* window,int ket,int scancode,int action,int mods){
	if(mood ==0 || mood==1){
		if(ket== GLFW_KEY_UP && action == GLFW_PRESS){
			monkey.translate(0.0,0.8,0.0);
			monkey.transformaMonkey(true,false);
		}
		if(ket== GLFW_KEY_RIGHT && action == GLFW_PRESS){
			monkey.translate(0.8,0.0,0.0);
			monkey.transformaMonkey(true,false);
		}
	
		if(ket== GLFW_KEY_LEFT && action == GLFW_PRESS){
			monkey.translate(-0.8,0.0,0.0);
			monkey.transformaMonkey(true,false);
		}
		if(ket== GLFW_KEY_DOWN && action == GLFW_PRESS){
			monkey.translate(0.0,-0.8,0.0);
			monkey.transformaMonkey(true,false);
		}
	}
	if(mood==2){
		if(ket== GLFW_KEY_UP && action == GLFW_PRESS){
			monkey.translate(-0.8,0.0,0.0);
			monkey.transformaMonkey(true,false);
		}
		if(ket== GLFW_KEY_RIGHT && action == GLFW_PRESS){
			monkey.translate(0.0,-0.8,0.0);
			monkey.transformaMonkey(true,false);
		}
	
		if(ket== GLFW_KEY_LEFT && action == GLFW_PRESS){
			monkey.translate(0.0,0.8,0.0);
			monkey.transformaMonkey(true,false);
		}
		if(ket== GLFW_KEY_DOWN && action == GLFW_PRESS){
			monkey.translate(0.8,0.0,0.0);
			monkey.transformaMonkey(true,false);
		}
	}
	if(ket== GLFW_KEY_0 && action == GLFW_PRESS){
		cout << "vista normal " << endl; 
		eye = {0.0, 0.0, 10.0};
		camera = {0.0, 0.0, 0.0};
		va = {0.0, 1.0, 0.0};
		mood =0;
	}
	if(ket== GLFW_KEY_1 && action == GLFW_PRESS){
		cout << "vista inversa " << endl; 
		eye = {0.0, 10.0, 0.0};
		camera = {0.0, 0.0, 10.0};
		va = {0.0, 0.0, -1.0};
		p1.translate(7.6,0,0);
		mood=1;
	}
	
	if(ket== GLFW_KEY_2 && action == GLFW_PRESS){
		cout << "vista arriba " << endl; 
		eye = {0.0, 10.0, 0.0};
		camera = {0.0, 0.0, 0.0};
		va = {-1.0, 0.0, 0.0};
		mood=2;
	}
}

void colision(){
	//Ecuación del plano Ax+By+Cz-D=0 Normal (A,B,C)
	bool bandera=false;
	int i=0;
	while(bandera==false && i<monkey.hit_boxM.vertex_list.size()){
		Vertex punto= monkey.hit_boxM.vertex_list[i];
		bandera=true;
		int j=0;
		while(bandera==true && j<pal.hit_box.face_list.size()){
			Face cara= pal.hit_box.face_list[j];
			float valor= (cara.A*punto.x)+(cara.B*punto.y)+(cara.C*punto.z)-cara.D;
			if(valor>0){
				//cout << "no choque"<< endl;
				bandera=false;
			}
			j++;
		}
		i++;
	}
	if(bandera== false){
		//cout <<" si hubo choque " << endl;
		pal.regresa();
	}
}

