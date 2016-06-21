#ifndef SAMPLE_H
#define SAMPLE_H

#include "Energy.h"

class Sample
{private:
	
public:
	Sample(Vertex* a, Vertex* b,Vertex* c,Vertex* d){vertices= new Vertex*[4]; vertices[0]=a;vertices[1]=b;vertices[2]=c;vertices[3]=d;}
	double Area();
	double Area1();
	void order();
	Vertex** bubblex(Vertex**,int);
	Vertex** bubbley(Vertex**,int);
	void Area_const();
	void Line_const();
	void Position_const();
	void print();
	double patchlength();
};

#endif