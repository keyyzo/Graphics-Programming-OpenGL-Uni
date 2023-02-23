#pragma once

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

class Sphere
{
protected:

	// declaring and initialising the value of pi

	float pi = 3.1415;

	// declaring values used within the creation of a sphere

	float theta, delta, longs, lats;
	float vx, vy, vz;
	
	float uCoord, vCoord;
	

public:

	// declares sphere constructor

	Sphere::Sphere();

	// render function that takes in two paramenters controlling 
	// the radius of the sphere and the resolution / num of quad

	void RenderSphere(float radius, int segments);
};

