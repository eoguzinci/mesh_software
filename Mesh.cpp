#include "Mesh.h"

using namespace Vec;
using namespace Sorting;

Mesh::Mesh(const Mesh & m) {
	for(int i=0;i<m.n_nodes;i++) 
	{n_nodes=m.n_nodes;
	n_faces=m.n_faces;
	vec_nodes[i]=m.vec_nodes[i];
	vec_faces[i]=m.vec_faces[i];
	Ad=m.Ad;
	p_curv=m.p_curv;
	}
	}

Mesh& Mesh::operator=(const Mesh& m) {    // copy assignment
  if (this != &m)                // beware of self-assignment like t = t;
		for(int i=0;i<m.n_nodes;i++) 
	{n_nodes=m.n_nodes;
	n_faces=m.n_faces;
	vec_nodes[i]=m.vec_nodes[i];
	vec_faces[i]=m.vec_faces[i];
	Ad=m.Ad;
	p_curv=m.p_curv;
	return *this;
}  
}


void Mesh::Adjacency() 
{int n1,n2,n3;

for (int i=0;i<n_faces;i++)
{
n1=vec_faces[i]->VertexA->num;
n2=vec_faces[i]->VertexB->num;
n3=vec_faces[i]->VertexC->num;

Ad[n1][n2]=1;
Ad[n1][n3]=1;
Ad[n2][n1]=1;
Ad[n2][n3]=1;
Ad[n3][n1]=1;
Ad[n3][n2]=1;
}
}

double Mesh::Area()
{double am=0;
for(int i=0;i<n_faces;i++) am+=vec_faces[i]->Area(); 
return am;
}

Vertex** Mesh::neigh(int n)			
{Vertex** vec_neigh=new Vertex*[n_nodes];
int am=vec_nodes[n]->num;
int m=0;
for(int i=0; i<n_nodes;i++)
{if (Ad[am][i]==1)
{	vec_neigh[m]=vec_nodes[i];
	m+=1;}
p_curv=&m;
int uncle=m;
while(uncle<n_nodes)
{delete[] vec_neigh[uncle];
uncle++;}
}
return vec_neigh;
}

double* Mesh::Curvature(int n)
{Vertex* ver=vec_nodes[n];
Vertex** nach=neigh(n);
double** vec_normal= new double* [8];
for(int i=0;i<*p_curv;i++)
{double* nomin=cross(nach[i]->subtr1(nach[i],ver),nach[i]->subtr1(nach[(i+1)%*p_curv],ver));
double denom=length(nomin);
vec_normal[i]=divide(nomin,denom);
}
double* ave_normal=new double[8];
for(int i=0;i<*p_curv;i++)
{ave_normal=add(ave_normal,vec_normal[i]);}
ave_normal=divide(ave_normal,*p_curv);
ave_normal=divide(ave_normal,length(ave_normal));
double* curvat=new double [8];
for(int i=0;i<*p_curv;i++)
curvat[i]=dot1(dot2(ave_normal,2),nach[i]->subtr1(nach[i],ver))/length(nach[i]->subtr1(nach[i],ver))/length(nach[i]->subtr1(nach[i],ver));
double* extreme=minmax(curvat,*p_curv);
delete[] curvat;
return extreme;
}


