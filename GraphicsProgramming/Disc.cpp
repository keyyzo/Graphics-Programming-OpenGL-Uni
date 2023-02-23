#include "Disc.h"

// disc constructor

Disc::Disc()
{
	
}

// initialises render function, taking in parameters and then rendering
// to the scene a disc based on those parameters

void Disc::RenderDisc(float diameter, int segments)
{
	// setting theta to 0
	// keeping interval and radius as set values throughout the calculations

	theta = 0;
	radius = diameter / 2;
	interval = (2 * pi) / segments;

	glBegin(GL_TRIANGLES);

	// segments controls resolution / number of triangles
	// within the disc


	for (int i = 0; i < segments; i++)
	{
		
			// set first normal, tex coord and vertice of triangle
			// centre of disc

			glNormal3f(0, 0, 1);
			glTexCoord2f(0.5,0.5);
			glVertex3f(0, 0, 0);

			

			// work out the second vertice position by
			// gaining the angle times radius

			vx = radius * cos(theta);
			vy = radius * sin(theta);

			// set second normal, tex coord and vertice of triangle
			// first outer vertice of triangle

			glNormal3f(0, 0, 1);
			glTexCoord2f(cos(theta)*0.5 + 0.5, (sin(theta) *0.5 + 0.5));
			glVertex3f(vx, vy, 0);

			// work out the third vertice position by updating the 
			// calculations needed

			vx = radius*cos(theta + interval);
			vy = radius*sin(theta + interval);

			// set third normal, tex coord and vertice of triangle
			// second outer verice of triangle

			glNormal3f(0, 0, 1);
			glTexCoord2f(cos(theta + interval) *0.5 + 0.5, (sin(theta + interval)* 0.5 + 0.5));
			glVertex3f(vx, vy, 0);

			// update the angle about the disc for calculations

		theta += interval;

		

	}

	// clamp last value back to 0 for centre of disc

	vx = radius *cos(0);
	vy = radius *sin(0);
	glVertex3f(vx, vy, 0);

	glEnd();
}

	
