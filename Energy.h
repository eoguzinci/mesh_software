#ifndef ENERGY_H
#define ENERGY_H

#include "Mesh.h"

class Energy
{private:
	Mesh* mnew;							//modified mesh
	Mesh* mold;							//reference mesh
	Vertex** vertices;					//constrained vertices in modified mesh
	Vertex** mvertices;					//constrained vertices in reference mesh
	double kareal,kconf,kcurve;			//coeefficients
	double lambda[5];					//Lagrange multipliers
public:
	Energy(Mesh* a,Mesh* am,int b, int c,int d,int e,double f, double g,double h)
	{mold=a; mnew=am; vertices= new Vertex*[4];
	vertices[0]=mnew->vec_nodes[b];vertices[1]=mnew->vec_nodes[c];vertices[2]=mnew->vec_nodes[d];vertices[3]=mnew->vec_nodes[e];
	mvertices= new Vertex*[4];
	mvertices[0]=mold->vec_nodes[b];mvertices[1]=mold->vec_nodes[c];mvertices[2]=mold->vec_nodes[d];mvertices[3]=mold->vec_nodes[e];
	kareal=f; kconf=g;kcurve=h;}
	double Areal_face(int);				//Areal deformation energy of face_i
	double Conformal_face(int);			//Conformal deformation energy of face_i
	double Curvature_mesh();			//Curvature deformation energy of whole mesh
	double Areal_mesh();				//Areal deformation energy of whole mesh
	double Conformal_mesh();			//Conformal deformation energy of whole mesh
	double Total_energy();				//Total deformation energy
	double Ave_area(int);				//Average of nearby the Vertex_i
	
	void Initialize();					//initializes Lagrange multipliers			
	double Area();						//
	double Area1();						//calculates are of the patch
	void order();						//orders Vertices sequence							for mesh new
	double length();					//calculates circumference of the patch				
	double sumx();						//sum of x values of the selected vertices
	double sumy();						//sum of y values of the selected vertices
	double sumz();						//sum of z values of the selected vertices
	
	double mArea();						
	double mArea1();
	void morder();
	double mlength();
	double msumx();
	double msumy();
	double msumz();
	
	Vertex** bubblex(Vertex**,int);		//bubble sort for x values of vertices
	Vertex** bubbley(Vertex**,int);		//bubble sort for y values of vertices
	void print();
	double patchlength();
	void movex(int,double);				//changes x values with a step size
	void movey(int,double);				//changes y values with a step size
	void movez(int,double);				//changes z values with a step size
	void Optimize();					//Newton's Method of Optimization
};

#endif