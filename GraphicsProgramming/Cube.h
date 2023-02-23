#pragma once

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>

class Cube
{
protected:

	// declaring vectors to store each respective values 
	// from the procedural generation

	std::vector<float> verts, normals, tex;

	// declaring float values for each value within the vectors
	// v - vector, n - normal, uC & vC - u and v texture coords

	float vx, vy, vz;
	float nx, ny, nz;
	float uC, vC;

public:

	// declares plane constructor

	Cube::Cube();

	// declares function that calculates the vertices
	// normals and texture coordinates of the plane
	// with taking the passed in parameter that controls 
	// the number of quads within the plane

	void CalculateCube(int segments);

	// declares function that will render the plane

	void RenderCube();

};

