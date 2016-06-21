#include "Sample.h"

using namespace Sorting;
using namespace Vec;

double Sample::Area()
{double a,b,c,d;
a=vertices[0]->x*vertices[1]->y-vertices[1]->x*vertices[0]->y;
b=vertices[1]->x*vertices[2]->y-vertices[2]->x*vertices[1]->y;
c=vertices[2]->x*vertices[3]->y-vertices[3]->x*vertices[2]->y;
d=vertices[3]->x*vertices[0]->y-vertices[0]->x*vertices[3]->y;
return (a+b+c+d)/2; 
}

void Sample::order()
{vertices=bubblex(vertices,4);
Vertex** left=new Vertex*[2];
Vertex** right=new Vertex*[2];
for(int i=0;i<2;i++) 
{left[i]=vertices[i];
right[i]=vertices[i+2];
}
left=bubbley(left,2);
right=bubbley(right,2);
vertices[0]=left[0];
vertices[1]=right[0];
vertices[2]=right[1];
vertices[3]=left[1];
}

double Sample::Area1()
{order();
return Area();
}

Vertex** Sample::bubblex(Vertex** b,int n)
{double temp=0;
Vertex* temp1;
double* a=new double[n];
for(int i=0;i<n;i++) a[i]=b[i]->x;
for(int j=0;j<n-1;j++)
{for(int i=0;i<(n-1-j);i++)
{if(a[n-1-i]<a[n-i-2])
{temp=a[n-1-i];
a[n-1-i]=a[n-1-i-1];
a[n-i-2]=temp;
temp1=b[n-1-i];
b[n-1-i]=b[n-1-i-1];
b[n-i-2]=temp1;}
}
}
return b;
}

Vertex** Sample::bubbley(Vertex** b,int n)
{double temp=0;
Vertex* temp1;
double* a=new double[n];
for(int i=0;i<n;i++) a[i]=b[i]->y;
for(int j=0;j<n-1;j++)
{for(int i=0;i<(n-1-j);i++)
{if(a[n-1-i]<a[n-i-2])
{temp=a[n-1-i];
a[n-1-i]=a[n-1-i-1];
a[n-i-2]=temp;
temp1=b[n-1-i];
b[n-1-i]=b[n-1-i-1];
b[n-i-2]=temp1;}
}
}
return b;
}

void Sample::print()
{for(int i=0;i<4;i++)
{vertices[i]->print();}
}


double Sample::patchlength()
{order();
return vertices[0]->lenth(vertices[0],vertices[1])+vertices[0]->lenth(vertices[1],vertices[2])+vertices[0]->lenth(vertices[2],vertices[3])+vertices[0]->lenth(vertices[3],vertices[0]);
}

void Sample::Area_const()
{Area1();
}