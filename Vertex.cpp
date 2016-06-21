#include "Vertex.h"

Vertex::Vertex(const Vertex & f) {
		num=f.num;
		x = f.x;
		y = f.y;
		z = f.z;
	}

Vertex& Vertex::operator=(const Vertex& f) {    // copy assignment
  if (this != &f)                // beware of self-assignment like f = f;
		num=f.num;
		x = f.x;
		y = f.y;
		z = f.z;
  return *this;
}

double* Vertex::subtr1(Vertex* a,Vertex* b)
{double* pr;
double c[3];
c[0]=a->x-b->x;
c[1]=a->y-b->y;
c[2]=a->z-b->z;
pr=c;
return pr;}

void Vertex::print(){cout<<num<<"\t"<<x<<"\t"<<y<<"\t"<<z<<endl;}

double Vertex::lenth(Vertex* a,Vertex* b)
{double x1,x2,y1,y2,z1,z2;

x1=a->getx();
x2=b->getx();
y1=a->gety();
y2=b->gety();
z1=a->getz();
z2=b->getz();

return sqrt(pow((x2-x1),2)+pow(y2-y1,2)+pow(z2-z1,2));
}