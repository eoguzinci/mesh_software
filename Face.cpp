#include "Face.h"

using namespace Vec;

Face::Face(const Face & f) {
		num=f.num;
		VertexA = f.VertexA;
		VertexB = f.VertexB;
		VertexC = f.VertexC;
	}

Face& Face::operator=(const Face& f) {    // copy assignment
  if (this != &f)                // beware of self-assignment like f = f;
		num=f.num;
		VertexA = f.VertexA;
		VertexB = f.VertexB;
		VertexC = f.VertexC;
  return *this;
}

double Face::edgel1()
{double x1,x2,y1,y2,z1,z2;

x1=VertexA->getx();
x2=VertexB->getx();
y1=VertexA->gety();
y2=VertexB->gety();
z1=VertexA->getz();
z2=VertexB->getz();

return sqrt(pow((x2-x1),2)+pow(y2-y1,2)+pow(z2-z1,2));	//calculating the length
}

double Face::edgel2()
{double x1,x2,y1,y2,z1,z2;

x1=VertexB->getx();
x2=VertexC->getx();
y1=VertexB->gety();
y2=VertexC->gety();
z1=VertexB->getz();
z2=VertexC->getz();

return sqrt(pow((x2-x1),2)+pow(y2-y1,2)+pow(z2-z1,2));	//calculating the length
}

double Face::edgel3()
{double x1,x2,y1,y2,z1,z2;

x1=VertexA->getx();
x2=VertexC->getx();
y1=VertexA->gety();
y2=VertexC->gety();
z1=VertexA->getz();
z2=VertexC->getz();

return sqrt(pow((x2-x1),2)+pow(y2-y1,2)+pow(z2-z1,2));	//calculating the length
}

double Face::angle1()
{double a,b,c;

c=edgel1();
b=edgel2();
a=edgel3();

return acos((pow(a,2)+pow(b,2)-pow(c,2))/2/a/b);	// find first angle points first edge in sinus theorem
}

double Face::angle2()
{double a,b,c;

c=edgel2();
b=edgel1();
a=edgel3();

return acos((pow(a,2)+pow(b,2)-pow(c,2))/2/a/b);	// find second angle points second edge in sinus theorem
}

double Face::angle3()
{double a,b,c;

c=edgel3();
b=edgel2();
a=edgel1();

return acos((pow(a,2)+pow(b,2)-pow(c,2))/2/a/b);	// find third angle points third edge in sinus theorem
}

double Face::Area()
{
	return edgel2()*edgel3()*sin(angle1())/2;		// finds the area
}

double* Face::unit_normal()
{double* nomin=cross(VertexA->subtr1(VertexA,VertexB),VertexA->subtr1(VertexC,VertexB)); 
double denom=length(nomin);
return divide(nomin,denom);
}