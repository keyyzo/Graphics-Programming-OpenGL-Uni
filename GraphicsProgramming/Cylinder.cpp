#include "Cylinder.h"

// cylinder constructor setting initial values

Cylinder::Cylinder()
{

	// initialising texture coordinates

	uCoords = 0;
	vCoords = 0;

	// initialising normals and vertice values

	vx = 0, vy = 0, vz = 0;
}

// initialises render function, taking in parameters and then rendering
// to the scene a cylinder based on those parameters

void Cylinder::RenderCylinder(float diameter, int segments, int height)
{
	// setting theta to 0
	// keeping interval and radius as set values throughout the calculations

	theta = 0;
	interval = (2 * pi) / segments;
	radius = diameter / 2;

	// back end of cylinder
	// using a disc with number of triangles passed in 
	// by parameter

	for (int i = 0; i < segments; i++)
	{

		glBegin(GL_TRIANGLES);

		// set first normal, tex coord and vertice of triangle
		// centre of disc

		glNormal3f(0, 0, -1);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, 0);

		// set second normal, tex coord and vertice of triangle
		// first outer vertice of triangle

		glNormal3f(0, 0, -1);
		glTexCoord2f((cos(theta) *0.5) + 0.5, (sin(theta) *0.5) + 0.5);
		glVertex3f(vx, vy, 0);

		// work out the third vertice position by updating the 
		// calculations needed
		

		vx = radius * cos(theta + interval);
		vy = radius * sin(theta + interval);

		// set third normal, tex coord and vertice of triangle
		// second outer verice of triangle

		glNormal3f(0, 0, -1);
		glTexCoord2f((cos(theta + interval) *0.5) + 0.5, (sin(theta + interval) *0.5) + 0.5);
		glVertex3f(vx, vy, 0);

		glEnd();

		// update the angle about the disc for calculations

		theta += interval;

		vx = radius * cos(theta);
		vy = radius * sin(theta);

	}

	// base of cylinder
	// number of quads within the cylinder and height of cylinder  
	// passed in by parameter

	glBegin(GL_QUADS);

	// nested for loops, each controlling height and num of quads
	// within one full circle from passed in parameters

		for (int i = 0; i < height; i++)
		{
			// resetting the angle once height increases

			theta = 0;

			for (int j = 0; j < segments; j++)
			{
				// set first normal, tex coord and vertice values of quad 
				// into respective variables

				vx = radius*cos(theta);
				vy = radius*sin(theta);
				vz = i;

				uCoords = ((float)j / segments);
				vCoords = ((float)i / height);

				// placing variable values into each function

				glTexCoord2f(uCoords, vCoords);
				glNormal3f(vx, vy, vz);
				glVertex3f(vx, vy, vz);

				// set second normal, tex coord and vertice values of quad
				// into respective variables

				vx = radius*cos(theta + interval);
				vy = radius*sin(theta + interval);
				vz = i;

				uCoords = ((float)(j + 1) / segments);
				vCoords = ((float)i / height);

				// placing variable values into each function

				glTexCoord2f(uCoords, vCoords);
				glNormal3f(vx, vy, vz);
				glVertex3f(vx, vy, vz);

				// set third normal, tex coord and vertice values of quad
				// into respective variables

				vx = radius*cos(theta + interval);
				vy = radius*sin(theta + interval);
				vz = i+1;

				uCoords = ((float)(j + 1) / segments);
				vCoords = ((float)(i + 1) / height);

				// placing variable values into each function

				glTexCoord2f(uCoords, vCoords);
				glNormal3f(vx, vy, vz);
				glVertex3f(vx, vy, vz);

				// set final normal, tex coord and vertice values of quad
				// into respective variables

				vx = radius*cos(theta);
				vy = radius*sin(theta);
				vz = i+1;
				 
				uCoords = ((float)j / segments);
				vCoords = ((float)(i + 1) / height);
				
				// placing variable values into each function

				glTexCoord2f(uCoords, vCoords);
				glNormal3f(vx, vy, vz);
				glVertex3f(vx, vy, vz);

				// increasing the angle for cal

				theta += interval;
			}
		}

	glEnd();

	// resetting the angle for drawing second disc
	// front disc at max height value

	// draws same disc as the back disc but uses the max height
	// as the constant z-value instead of 0

	theta = 0;

	for (int i = 0; i < segments; i++)
	{

		glBegin(GL_TRIANGLES);

		glNormal3f(0, 0, 1);
		glTexCoord2f(0.5, 0.5);
		glVertex3f(0, 0, height);

		glNormal3f(0, 0, 1);
		glTexCoord2f((cos(theta) *0.5) + 0.5, (sin(theta) *0.5) + 0.5);
		glVertex3f(vx, vy, height);

		vx = radius * cos(theta + interval);
		vy = radius * sin(theta + interval);

		glNormal3f(0, 0, 1);
		glTexCoord2f((cos(theta + interval) *0.5) + 0.5, (sin(theta + interval) *0.5) + 0.5);
		glVertex3f(vx, vy, height);

		glEnd();

		theta += interval;

		vx = radius * cos(theta);
		vy = radius * sin(theta);

	}

} 