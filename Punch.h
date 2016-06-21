#ifndef PUNCH_H
#define PUNCH_H

#include "Energy.h"

class Punch
{private:
	double x,y,z,r;
	friend class Energy;
public:
	Punch(double a,double b){x=a; y=b; z=0; r=0.25;}
	void Area_const();
	void Line_const();
	void Curvature_const();
	void Position_const();
};

#endif