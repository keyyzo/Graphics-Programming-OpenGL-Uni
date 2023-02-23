#pragma once

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

class Cylinder
{
protected:

	// declaring and initialising the value of pi

	float pi = 3.1415;

	// declaring values used within the creation of a cylinder

	float theta, interval;
	float vx, vy, vz;

	float uCoords, vCoords;
	float radius, diameter;

public:

	// declares cylinder constructor

	Cylinder::Cylinder();

	// render function that takes in three paramenters controlling 
	// the diameter and height of the cylinder and the resolution / num of quads

	void RenderCylinder(float diameter, int segments, int height);

};

