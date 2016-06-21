#include "Energy.h"
#include <stdio.h>

using namespace Vec;
using namespace Sorting;

double Energy::Areal_face(int n)
{double a1,a2;
a1=mold->vec_faces[n]->Area();
a2=mnew->vec_faces[n]->Area();
return a1/a2+a2/a1;
}

double Energy::Conformal_face(int n)
{double a2,angle1,angle2,angle3,edge1,edge2,edge3;
angle1=mold->vec_faces[n]->angle1();
angle2=mold->vec_faces[n]->angle2();
angle3=mold->vec_faces[n]->angle3();
edge1=mnew->vec_faces[n]->edgel1();
edge2=mnew->vec_faces[n]->edgel2();
edge3=mnew->vec_faces[n]->edgel3();
a2=mnew->vec_faces[n]->Area();

return (edge1*edge1/tan(angle1)+edge2*edge2/tan(angle2)+edge3*edge3/tan(angle3))/2/a2;
}

double Energy::Areal_mesh()
{int n=mold->n_faces;
double sum=0;
for(int i=0;i<n;i++) sum+=Areal_face(i)*mold->vec_faces[i]->Area();
return sum/mold->Area();
}

double Energy::Conformal_mesh()
{int n=mold->n_faces;
double sum;
sum=0;
for(int i=0;i<n;i++) sum+=Conformal_face(i)*mold->vec_faces[i]->Area();
return sum/mold->Area();
}

double Energy::Ave_area(int n)
{	Vertex** nach=mold->neigh(n);
	Face** neigh_face=new Face* [8];
	int m=0;
	for(int i=0;i<mold->n_faces;i++)
	{if(mold->vec_faces[i]->VertexA->num==n||mold->vec_faces[i]->VertexB->num==n||mold->vec_faces[i]->VertexC->num==n)
	{neigh_face[m]=mold->vec_faces[i];
	m+=1;}
	}
	double sum=0;
	for(int i=0;i<m;i++)
		sum+=neigh_face[i]->Area();
	return sum/m;
}

double Energy::Curvature_mesh()
{int n=mold->n_nodes;
double sum=0;	
for(int i=0;i<n;i++)
sum+=Ave_area(i)*((mnew->Curvature(i)[0]-mold->Curvature(i)[0])*(mnew->Curvature(i)[0]-mold->Curvature(i)[0])+(mnew->Curvature(i)[1]-mold->Curvature(i)[1])*(mnew->Curvature(i)[1]-mold->Curvature(i)[1]));
return sum;	
}

double Energy::Total_energy()
{return kareal*Areal_mesh()+kconf*Conformal_mesh();}

void Energy::Initialize()
{for(int i=0;i<5;i++) lambda[i]=0;}

double Energy::Area()
{double a,b,c,d;
a=vertices[0]->x*vertices[1]->y-vertices[1]->x*vertices[0]->y;
b=vertices[1]->x*vertices[2]->y-vertices[2]->x*vertices[1]->y;
c=vertices[2]->x*vertices[3]->y-vertices[3]->x*vertices[2]->y;
d=vertices[3]->x*vertices[0]->y-vertices[0]->x*vertices[3]->y;
return (a+b+c+d)/2; 
}

void Energy::order()
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

double Energy::Area1()
{order();
return Area();
}

double Energy::length()
{order();
Face a(201,vertices[0],vertices[1],vertices[3]);
Face b(202,vertices[1],vertices[2],vertices[3]);
return a.edgel1()+b.edgel1()+b.edgel2()+a.edgel3();
}

double Energy::sumx()
{return vertices[0]->getx()+vertices[1]->getx()+vertices[2]->getx()+vertices[3]->getx();}

double Energy::sumy()
{return vertices[0]->gety()+vertices[1]->gety()+vertices[2]->gety()+vertices[3]->gety();}

double Energy::sumz()
{return vertices[0]->getz()+vertices[1]->getz()+vertices[2]->getz()+vertices[3]->getz();}

double Energy::mArea()
{double a,b,c,d;
a=mvertices[0]->x*mvertices[1]->y-mvertices[1]->x*mvertices[0]->y;
b=mvertices[1]->x*mvertices[2]->y-mvertices[2]->x*mvertices[1]->y;
c=mvertices[2]->x*mvertices[3]->y-mvertices[3]->x*mvertices[2]->y;
d=mvertices[3]->x*mvertices[0]->y-mvertices[0]->x*mvertices[3]->y;
return (a+b+c+d)/2; 
}

void Energy::morder()
{mvertices=bubblex(mvertices,4);
Vertex** left=new Vertex*[2];
Vertex** right=new Vertex*[2];
for(int i=0;i<2;i++) 
{left[i]=mvertices[i];
right[i]=mvertices[i+2];
}
left=bubbley(left,2);
right=bubbley(right,2);
mvertices[0]=left[0];
mvertices[1]=right[0];
mvertices[2]=right[1];
mvertices[3]=left[1];
}

double Energy::mArea1()
{morder();
return mArea();
}

double Energy::mlength()
{morder();
Face a(201,mvertices[0],mvertices[1],mvertices[3]);
Face b(202,mvertices[1],mvertices[2],mvertices[3]);
return a.edgel1()+b.edgel1()+b.edgel2()+a.edgel3();
}

double Energy::msumx()
{return mvertices[0]->getx()+mvertices[1]->getx()+mvertices[2]->getx()+mvertices[3]->getx();}

double Energy::msumy()
{return mvertices[0]->gety()+mvertices[1]->gety()+mvertices[2]->gety()+mvertices[3]->gety();}

double Energy::msumz()
{return mvertices[0]->getz()+mvertices[1]->getz()+mvertices[2]->getz()+mvertices[3]->getz();}


Vertex** Energy::bubblex(Vertex** b,int n)
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

Vertex** Energy::bubbley(Vertex** b,int n)
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

void Energy::print()
{for(int i=0;i<4;i++)
{vertices[i]->print();}
}


double Energy::patchlength()
{order();
return vertices[0]->lenth(vertices[0],vertices[1])+vertices[0]->lenth(vertices[1],vertices[2])+vertices[0]->lenth(vertices[2],vertices[3])+vertices[0]->lenth(vertices[3],vertices[0]);
}

void Energy::movex(int i,double m)
{
	mnew->vec_nodes[i]->x=mnew->vec_nodes[i]->x+m;
}

void Energy::movey(int i,double m)
{
	mnew->vec_nodes[i]->y=mnew->vec_nodes[i]->y+m;
}

void Energy::movez(int i,double m)
{
	mnew->vec_nodes[i]->z=mnew->vec_nodes[i]->z+m;
}

void Energy::Optimize()
{Initialize();
double step=0.005;

double** vec_soln=new double* [3*mold->n_nodes+5];
for(int i=0;i<3*mold->n_nodes;i++)
{if(i%3==0) vec_soln[i]=&mnew->vec_nodes[i/3]->x;
if(i%3==1) vec_soln[i]=&mnew->vec_nodes[i/3]->y;
if(i%3==2) vec_soln[i]=&mnew->vec_nodes[i/3]->z;
}
for(int i=3*mold->n_nodes;i<3*mold->n_nodes+5;i++) vec_soln[i]=&lambda[i-3*mold->n_nodes];

for(int i=0;i<3*mold->n_nodes+5;i++) cout<<*vec_soln[i]<<endl;

cout<<endl<<endl;

int itera=0;
double err=0;

double A_ini=mArea1();
double l_ini=mlength();
double xsi=msumx();
double ysi=msumy();
double zsi=msumz();

double const1=mArea1()/4;
double const2=mlength()/2;
double const3=msumx();
double const4=msumy();
double const5=msumz();

do
{double* vec_solnold=new double [3*mold->n_nodes+5];
for(int i=0;i<3*mold->n_nodes+5;i++) vec_solnold[i]=(*vec_soln[i]); 

ofstream soln;
soln.open ("initial.txt");
for(int i=0;i<3*mold->n_nodes+5;i++)
{soln<<vec_solnold[i]<<endl;}
soln.close();

double* gradient=new double [3*mold->n_nodes+5];
double** Jacobian= new double* [3*mold->n_nodes+5];
for(int j=0;j<3*mold->n_nodes+5;j++) Jacobian[j]=new double [3*mold->n_nodes+5];


double f0=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);


double f1,f12,f2,f3,f4,f5;

for(int i=0;i<3*mold->n_nodes;i++)
{if(i%3==0) 
{/*cout<<"x[0]old:"<<mnew->vec_nodes[i/3]->x<<endl;
cout<<"x[0]const:"<<mold->vec_nodes[i/3]->x<<endl;
cout<<"Total Energy 1:"<<Total_energy()<<"\t";
cout<<"Areal Energy 1:"<<Areal_mesh()<<"\t";
cout<<"Areal Face 1:"<<Areal_face(1)<<endl;
cout<<"Face1:"<<"\t"<<mnew->vec_faces[1]->VertexA->num<<"\t"<<mnew->vec_faces[1]->VertexB->num<<"\t"<<mnew->vec_faces[1]->VertexC->num<<"\t"<<endl;
cout<<"Area mold 1:"<<mold->vec_faces[1]->Area()<<endl;
cout<<"Area mnew 1:"<<mnew->vec_faces[1]->Area()<<endl<<endl;*/
movex(i/3,step);
/*cout<<"x[0]new:"<<mnew->vec_nodes[i/3]->x<<endl;
cout<<"x[0]const:"<<mold->vec_nodes[i/3]->x<<endl;
cout<<"Total Energy 2:"<<Total_energy()<<"\t";
cout<<"Areal Energy 2:"<<Areal_mesh()<<"\t";
cout<<"Areal Face 2:"<<Areal_face(1)<<endl;
cout<<"Area mold 2:"<<mold->vec_faces[1]->Area()<<endl;
cout<<"Area mnew 2:"<<mnew->vec_faces[1]->Area()<<endl<<endl;*/
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
gradient[i]=(f1-f0)/step;
movex(i/3,-step);
/*cout<<"x[0]new:"<<mnew->vec_nodes[i/3]->x<<endl;
cout<<"x[0]const:"<<mold->vec_nodes[i/3]->x<<endl;
cout<<"Total Energy 2:"<<Total_energy()<<"\t";
cout<<"Areal Energy 2:"<<Areal_mesh()<<"\t";
cout<<"Areal Face 2:"<<Areal_face(0)<<endl;
cout<<"Area mold 2:"<<mold->vec_faces[0]->Area()<<endl;
cout<<"Area mnew 2:"<<mnew->vec_faces[0]->Area()<<endl<<endl;*/}
if(i%3==1)
{movey(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
gradient[i]=(f1-f0)/step;
movey(i/3,-step);}
if(i%3==2)
{movez(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
gradient[i]=(f1-f0)/step;
movez(i/3,-step);}
}
gradient[3*mold->n_nodes]=Area1()-const1;
gradient[3*mold->n_nodes+1]=length()-const2;
gradient[3*mold->n_nodes+2]=sumx()-const3;
gradient[3*mold->n_nodes+3]=sumy()-const4;
gradient[3*mold->n_nodes+4]=sumz()-const5;

ofstream grad;
grad.open ("gradient.txt");
for(int i=0;i<3*mold->n_nodes+5;i++)
{grad<<gradient[i]<<endl;}
grad.close();

/*for(int i=0;i<3*mold->n_nodes+5;i++) cout<<gradient[i]<<endl;
cout<<endl;*/
/*for(int i=0;i<3*mold->n_nodes+5;i++) 
{cout<<*vec_soln[i]<<"\t";
if(i%3==2) cout<<endl;}*/

for(int i=0;i<3*mold->n_nodes;i++)
{for(int j=0;j<3*mold->n_nodes;j++)
{if(i%3==0)
{if(j%3==0)
{movex(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movex(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-2*f1+f0)/step/step;
movex(i/3,-2*step);}
if(j%3==1)
{movex(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movey(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movex(i/3,-step);
f2=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-f1-f2+f0)/step/step;
movey(j/3,-step);}
if(j%3==2)
{movex(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movez(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movex(i/3,-step);
f2=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-f1-f2+f0)/step/step;
movez(j/3,-step);}
}
if(i%3==1)
{if(j%3==0)
{movey(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movex(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movey(i/3,-step);
f2=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-f1-f2+f0)/step/step;
movex(j/3,-step);}
if(j%3==1)
{movey(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movey(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-2*f1+f0)/step/step;
movey(i/3,-2*step);}
if(j%3==2)
{movey(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movez(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movey(i/3,-step);
f2=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-f1-f2+f0)/step/step;
movez(j/3,-step);}
}
if(i%3==2)
{if(j%3==0)
{movez(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movex(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movez(i/3,-step);
f2=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-f1-f2+f0)/step/step;
movex(j/3,-step);}
if(j%3==1)
{movez(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movey(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movez(i/3,-step);
f2=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-f1-f2+f0)/step/step;
movey(j/3,-step);}
if(j%3==2)
{movez(i/3,step);
f1=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
movez(j/3,step);
f12=Total_energy()+lambda[0]*(Area1()-const1)+lambda[1]*(length()-const2)+lambda[2]*(sumx()-const3)+lambda[3]*(sumy()-const4)+lambda[4]*(sumz()-const5);
	Jacobian[i][j]=(f12-2*f1+f0)/step/step;
movez(i/3,-2*step);}
}
}
}

cout<<endl<<endl;
for(int i=0;i<3*mold->n_nodes+5;i++)
{cout<<*vec_soln[i]<<"\t";
if(i%3==2) cout<<endl;}

double f01,f02,f03,f04,f05;
f01=Area1()-const1;
f02=length()-const2;
f03=sumx()-const3;
f04=sumy()-const4;
f05=sumz()-const5;

cout<<endl;
cout<<"*** "<<f01<<" ***"<<endl;

for(int i=0;i<3*mold->n_nodes;i++)
{if(i%3==0)
{movex(i/3,step);
f1=Area1()-const1;
Jacobian[3*mold->n_nodes][i]=(f1-f01)/step;
Jacobian[i][3*mold->n_nodes]=Jacobian[3*mold->n_nodes][i];
f2=length()-const2;
Jacobian[1+3*mold->n_nodes][i]=(f2-f02)/step;
Jacobian[i][1+3*mold->n_nodes]=Jacobian[1+3*mold->n_nodes][i];
f3=sumx()-const3;
Jacobian[2+3*mold->n_nodes][i]=(f3-f03)/step;
Jacobian[i][2+3*mold->n_nodes]=Jacobian[2+3*mold->n_nodes][i];
f4=sumy()-const4;
Jacobian[3+3*mold->n_nodes][i]=(f4-f04)/step;
Jacobian[i][3+3*mold->n_nodes]=Jacobian[3+3*mold->n_nodes][i];
f5=sumz()-const5;
Jacobian[4+3*mold->n_nodes][i]=(f5-f05)/step;
Jacobian[i][4+3*mold->n_nodes]=Jacobian[4+3*mold->n_nodes][i];
movex(i/3,-step);}
if(i%3==1)
{movey(i/3,step);
f1=Area1()-const1;
Jacobian[3*mold->n_nodes][i]=(f1-f01)/step;
Jacobian[i][3*mold->n_nodes]=Jacobian[3*mold->n_nodes][i];
f2=length()-const2;
Jacobian[1+3*mold->n_nodes][i]=(f2-f02)/step;
Jacobian[i][1+3*mold->n_nodes]=Jacobian[1+3*mold->n_nodes][i];
f3=sumx()-const3;
Jacobian[2+3*mold->n_nodes][i]=(f3-f03)/step;
Jacobian[i][2+3*mold->n_nodes]=Jacobian[2+3*mold->n_nodes][i];
f4=sumy()-const4;
Jacobian[3+3*mold->n_nodes][i]=(f4-f04)/step;
Jacobian[i][3+3*mold->n_nodes]=Jacobian[3+3*mold->n_nodes][i];
f5=sumz()-const5;
Jacobian[4+3*mold->n_nodes][i]=(f5-f05)/step;
Jacobian[i][4+3*mold->n_nodes]=Jacobian[4+3*mold->n_nodes][i];
movey(i/3,-step);}
if(i%3==2)
{movez(i/3,step);
f1=Area1()-const1;
Jacobian[3*mold->n_nodes][i]=(f1-f01)/step;
Jacobian[i][3*mold->n_nodes]=Jacobian[3*mold->n_nodes][i];
f2=length()-const2;
Jacobian[1+3*mold->n_nodes][i]=(f2-f02)/step;
Jacobian[i][1+3*mold->n_nodes]=Jacobian[1+3*mold->n_nodes][i];
f3=sumx()-const3;
Jacobian[2+3*mold->n_nodes][i]=(f3-f03)/step;
Jacobian[i][2+3*mold->n_nodes]=Jacobian[2+3*mold->n_nodes][i];
f4=sumy()-const4;
Jacobian[3+3*mold->n_nodes][i]=(f4-f04)/step;
Jacobian[i][3+3*mold->n_nodes]=Jacobian[3+3*mold->n_nodes][i];
f5=sumz()-const5;
Jacobian[4+3*mold->n_nodes][i]=(f5-f05)/step;
Jacobian[i][4+3*mold->n_nodes]=Jacobian[4+3*mold->n_nodes][i];
movez(i/3,-step);}
}

/*cout<<endl<<endl;
for(int i=0;i<3*mold->n_nodes+5;i++)
{cout<<*vec_soln[i]<<"\t";
if(i%3==2) cout<<endl;}*/

for(int i=3*mold->n_nodes;i<3*mold->n_nodes+5;i++)
{for(int j=3*mold->n_nodes;j<3*mold->n_nodes+5;j++) Jacobian[i][j]=0.00001;}

ofstream hes;
hes.open ("hessian.txt");
for(int i=0;i<3*mold->n_nodes+5;i++)
{for(int j=0;j<3*mold->n_nodes+5;j++)
{hes.width(16);
hes<<Jacobian[i][j];}
hes<<endl;}
hes.close();

/*for(int i=0;i<3*mold->n_nodes+5;i++)
{for(int j=0;j<3*mold->n_nodes+5;j++)
{cout.width(10);
cout<<Jacobian[i][j];
}
cout<<endl<<endl;
}*/

double* disp=new double [3*mold->n_nodes+5];
for(int i=0;i<3*mold->n_nodes+5;i++) disp[i]=0;

double* dispnew=new double [3*mold->n_nodes+5];
for(int i=0;i<3*mold->n_nodes+5;i++) dispnew[i]=0;

int iter=0;
double max_err=0.001;
double error=0;

/*do
{for(int i=0;i<3*mold->n_nodes+5;i++)
{double sum1,sum2; sum1=0; sum2=0;
for(int j=0;j<i;j++) sum1+=Jacobian[i][j]*dispnew[j];
for(int j=i+1;j<3*mold->n_nodes+5;j++) sum2+=Jacobian[i][j]*disp[j];
dispnew[i]=-(sum1+sum2+gradient[i])/Jacobian[i][i];
}
error=maxdiff(dispnew,disp);
iter++;
for(int i=0;i<3*mold->n_nodes+5;i++) disp[i]=dispnew[i];
for(int i=0;i<3*mold->n_nodes+5;i++) cout<<disp[i]<<endl;
cout<<endl<<error<<endl;
}while(error>max_err && iter<15);*/

Mtx hess(3*mold->n_nodes+5);
Vcr gradi(3*mold->n_nodes+5);

for(int i=0;i<3*mold->n_nodes+5;i++)	
{for(int j=0;j<3*mold->n_nodes+5;j++) {hess[i][j]=Jacobian[i][j];}
gradi[i]=-gradient[i];
}

hess.GaussElim(gradi);
cout<<endl<<endl;
gradi.print();
cout<<endl<<endl;

for(int i=0;i<3*mold->n_nodes+5;i++) *vec_soln[i]+=gradi[i];

cout<<endl<<endl;
for(int i=0;i<3*mold->n_nodes+5;i++)
{cout<<*vec_soln[i]<<"\t";
if(i%3==2) cout<<endl;}

double* vec_solnnew=new double [3*mold->n_nodes+5];
for(int i=0;i<3*mold->n_nodes+5;i++) vec_solnnew[i]=(*vec_soln[i]);

err=maxdiff(vec_solnnew,vec_solnold);
itera++;

for(int i=0;i<3*mold->n_nodes+5;i++) vec_solnold[i]=vec_solnnew[i];

}while(err>0.001&&itera<1);

/*cout<<endl<<endl;
for(int i=0;i<3*mold->n_nodes+5;i++)
{cout<<*vec_soln[i]<<"\t";
if(i%3==2) cout<<endl;}*/

double A_end=Area1();
double l_end=length();
double xse=sumx();
double yse=sumy();
double zse=sumz();

ofstream sonuc;
sonuc.open("final.txt");
sonuc<<"kareal:"<<kareal<<endl;
sonuc<<"kconf:"<<kconf<<endl;

sonuc<<endl;
sonuc<<"Initial Area:"<<A_ini<<"\t" ;
sonuc<<"Initial length:"<<l_ini<<"\t" ;
sonuc<<"Initial x:"<<xsi/4<<"\t";
sonuc<<"Initial y:"<<ysi/4<<"\t";
sonuc<<"Initial z:"<<zsi/4<<"\t";
sonuc<<endl;

sonuc<<endl;
sonuc<<"Objective Area:"<<A_ini/4<<"\t" ;
sonuc<<"Objective length:"<<l_ini/2<<"\t" ;
sonuc<<"Objective x:"<<xsi/4<<"\t";
sonuc<<"Objective y:"<<ysi/4<<"\t";
sonuc<<"Objective z:"<<zsi/4<<"\t";
sonuc<<endl;

sonuc<<endl;
sonuc<<"Final Area:"<<A_end<<"\t" ;
sonuc<<"Final length:"<<l_end<<"\t" ;
sonuc<<"Final x:"<<xse/4<<"\t";
sonuc<<"Final y:"<<yse/4<<"\t";
sonuc<<"Final z:"<<zse/4<<"\t";
sonuc<<endl;
sonuc.close();

ofstream myfile;
myfile.open ("outputtrial.off");
myfile<<"OFF"<<endl;;
myfile<<mold->n_nodes<<" ";
myfile<<mold->n_faces<<" ";
myfile<<0<<" "<<endl;
for(int i=0;i<3*mold->n_nodes;i++)
{myfile <<*vec_soln[i]<<" ";
if(i%3==2) myfile<<endl;}
for(int i=0;i<mold->n_faces;i++)
{myfile<<3<<" ";
myfile<<mnew->vec_faces[i]->VertexA->num<<" ";
myfile<<mnew->vec_faces[i]->VertexB->num<<" ";
myfile<<mnew->vec_faces[i]->VertexC->num<<" "<<endl;}
myfile.close();
}

