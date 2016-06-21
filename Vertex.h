#ifndef VERTEX_H
#define VERTEX_H

#include "lib.h"

class Vertex
{public:
int num;
double x,y,z;

	Vertex() {num=365; x=365.0; y=365.0; z=365.0;}
	Vertex(int d, double a,double b,double c)
	{x=a; y=b; z=c; num=d;}
	Vertex(const Vertex&);                   // copy constructor
	Vertex& operator=(const Vertex&);         //copy assignment 

	double getnum() {return num;};
	double getx(){return x;};
	double gety(){return y;};
	double getz(){return z;};
	double* subtr1(Vertex*,Vertex*);
	void print();
	double lenth(Vertex*,Vertex*);
};

#endif