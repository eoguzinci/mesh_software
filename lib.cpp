#include "lib.h"

double Vec::length(double a[])
{return sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);}

double* Vec::subtr2(double* a,double* b)
{double* pr;
double c[3];
c[0]=a[0]-b[0];
c[1]=a[1]-b[1];
c[2]=a[2]-b[2];
pr=c;
return pr;}

double Vec::dot1(double* a, double* b)
{double c;
c=a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
return c;}

double* Vec::dot2(double* a, double b)
{double* c;
c[0]=a[0]*b;
c[1]=a[1]*b;
c[2]=a[2]*b;
return c;}

double* Vec::cross(double* a,double* b)
{double* c;
c[0]= a[1]*b[2]-a[2]*b[1];
c[1]=a[2]*b[0]-a[0]*b[2];
c[2]=a[0]*b[1]-a[1]*b[0];
return c;
}

double* Vec::divide(double* a,double b)
{double* c;
c[0]=a[0]/b;
c[1]=a[1]/b;
c[2]=a[2]/b;
return c;
}

double* Vec::add(double* a,double* b)
{double* c;
c[0]=a[0]+b[0];
c[1]=a[1]+b[1];
c[2]=a[2]+b[2];
return c;
}

double* Sorting::bubble(double* a,int n)
{double temp=0;
for(int j=0;j<n-1;j++)
{for(int i=0;i<(n-1-j);i++)
{if(a[n-1-i]<a[n-i-2])
{temp=a[n-1-i];
a[n-1-i]=a[n-1-i-1];
a[n-i-2]=temp;}
}
}
return a;
}

double* Sorting::minmax(double* a,int n)
{double* reg=bubble(a,n);
double extreme[]={reg[0],reg[n-1]};
return extreme;
}

double Sorting::maxdiff(double* a,double* b)
{int n=sizeof(a);
double* c= new double [n];
if(n==sizeof(b))
{for(int i=0;i<n;i++) c[i]=fabs(a[i]-b[i]);}
double* d=minmax(c,n);
return d[1];
}

