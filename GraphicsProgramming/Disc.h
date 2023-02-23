#pragma once



#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>


class Disc
{
protected:

	// declaring float values used within the calculation
	// and creation of the disc

	// initialising pi value

	float radius, theta, pi = 3.1415;
	float interval;
	float vx, vy;
	

public:

	// declares disc constructor

	Disc::Disc();
	
	// render function that takes in two paramenters controlling 
	// the diameter and the resolution / num of triangles
	// within the disc

	void RenderDisc(float diameter, int segments);
};

