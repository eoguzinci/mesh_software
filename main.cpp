#include "lib.h"
#include "Energy.h"

int main (void)
{char ax,bx,cx;									//dummy characaters for 'OFF' file
int n_points,n_faces,s,mn_points,mn_faces,ps;	
double kareal, kconf, kcurve;					//weights on areal, conformal and curvature energies

kareal=0.0;
kconf=1.0;
kcurve=0.0;

ifstream infile ("tinymesh.off");				//reading from the file to inialize the mesh which will be modified
infile>>ax;
infile>>bx;
infile>>cx;
infile>>n_points;								//number of nodes
infile>>n_faces;								//number of faces
infile>>s;
	
Vertex** v=new Vertex* [n_points];

for(int i=0;i<n_points;i++)
{
	double x_i,y_i,z_i;
	infile >> x_i;						//taking x values from the file
	infile >> y_i;						//taking y values from the file
	infile >> z_i;						//taking z values from the file
	v[i] = new Vertex (i,x_i,y_i,z_i);	//setting up the data members of Vertex via constructor
}

Face** f=new Face* [n_faces];

for(int i=0;i<n_faces;i++)
{	int a,b,c,d;
	infile>>d;							//'3' means triangle
	infile>>a;							//VertexA number
	infile>>b;							//VertexB number
	infile>>c;							//VertexC number
	f[i]=new Face(i+1,v[a],v[b],v[c]);	//setting up the data members for Face via constructor
}

infile.close();

ifstream mat("tinymesh.off");			//same procedure for initializing the reference mesh(not modified) 

mat>>ax;
mat>>bx;
mat>>cx;
mat>>mn_points;
mat>>mn_faces;
mat>>ps;
	
Vertex** vm=new Vertex* [n_points];

for(int i=0;i<n_points;i++)
{
	double x_i,y_i,z_i;
	mat >> x_i;						//taking x values from the file
	mat >> y_i;						//taking y values from the file
	mat >> z_i;						//taking z values from the file
	vm[i] = new Vertex (i,x_i,y_i,z_i);	//setting up the data members of Node via constructor
}

Face** fm=new Face* [n_faces];

for(int i=0;i<n_faces;i++)
{	int a,b,c,d;
	mat>>d;
	mat>>a;
	mat>>b;
	mat>>c;
	fm[i]=new Face(i+1,vm[a],vm[b],vm[c]);
}
mat.close();

Mesh m(v,f,n_points,n_faces);							//construction of changable mesh(meshnew)
m.Adjacency();											//calculating adjacency matrix of meshnew

Mesh am(vm,fm,mn_points,mn_faces);						//construction of reference mesh(meshold)
am.Adjacency();											//calculating adjacency matrix of mesold

Energy e(&m,&am,5,6,9,10,kareal,kconf,kcurve);			//introducing the meshes, by giving which Vertices will be modified 
e.Optimize();											//Optimize

system ("PAUSE");
return 0;
}