#ifndef MESH_H
#define MESH_H

#include "lib.h"
#include "Face.h"
#include "Vertex.h"

class Mesh
{public:
	Vertex** vec_nodes;			//holds the vector of addresses to nodes
	Face** vec_faces;			//holds the vector of addresses to faces
	int n_nodes;				//number of nodes
	int n_faces;				//number of faces
	int** Ad;					//adjacency matrix (n_nodes x n_nodes)
	int* p_curv;				//number of neighbours(dummy) 
	
	Mesh(Vertex** a_m, Face** b_m, int c_m, int d_m)
	{vec_nodes=a_m; vec_faces=b_m; n_nodes=c_m; n_faces=d_m; Ad=new int* [c_m];
	for(int i=0;i<c_m;i++) Ad[i]=new int [c_m]; 
	}
	Mesh(const Mesh&);                   // copy constructor
	Mesh& operator=(const Mesh&);         //copy assignment 


	void Adjacency();					//fills the adjacency matrix
	double Area();						//finds the total area
	Vertex** neigh(int);				//finds the neighbours of the ith vertex
	double* Curvature(int);				//finds the min and max curvatures of the ith vertex
};

#endif
