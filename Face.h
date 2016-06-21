#ifndef FACE_H
#define FACE_H

#include "lib.h"
#include "Vertex.h"

class Face
{public:
	int num;
	Vertex* VertexA;
	Vertex* VertexB;
	Vertex* VertexC;
	Face(int n,Vertex* a,Vertex* b,Vertex* c) {num=n; VertexA=a; VertexB=b; VertexC=c;}
	Face(const Face&);                   // copy constructor
	Face& operator=(const Face&);         //copy assignment 

	double edgel1();		//calculating the length of edge1
	double edgel2();		//calculating the length of edge2
	double edgel3();		//calculating the length of edge3
	double angle1();		// find 1st angle points 1st edge in sinus theorem
	double angle2();		// find 2nd angle points 2nd edge in sinus theorem
	double angle3();		// find 3rd angle points 3rd edge in sinus theorem
	double Area();			// finds the area
	double* unit_normal();	//finds the unit normal of face
};

#endif