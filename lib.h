#ifndef LIB_H
#define LIB_H

#include "Matvec.h"
#include "Vertex.h"
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

namespace Vec{
	double length(double*);				//finds the absolute value of a vector
	double* subtr2(double*,double*);	//vector subtract of vertices
	double dot1(double*, double*);		//dot product of vectors
	double* dot2(double*,double);		//dot product with a scalar
	double* cross(double*,double*);		//cross product
	double* divide(double*,double);		//vector division with a scalar
	double* add(double*,double*);		//vector sum
}

namespace Triangle{
double edgel1();		//calculating the length of edge1
	double edgel2();		//calculating the length of edge2
	double edgel3();		//calculating the length of edge3
	double angle1();		// find 1st angle points 1st edge in sinus theorem
	double angle2();		// find 2nd angle points 2nd edge in sinus theorem
	double angle3();		// find 3rd angle points 3rd edge in sinus theorem
	double Area();			// finds the area
	double* unit_normal();	//finds the unit normal of face
}
namespace Sorting
{	double* bubble(double*,int);			//bubble sort
	double* minmax(double*,int);			//finds min and max
	double maxdiff(double*,double*);		//finds max difference between two vectors
}
#endif