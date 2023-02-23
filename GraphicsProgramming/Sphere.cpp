#include "Sphere.h"

// cylinder constructor setting initial values

Sphere::Sphere()
{
	
	// initialising texture coordinates

	uCoord = 0;
	vCoord = 0;

}

// initialises render function, taking in parameters and then rendering
// to the scene a sphere based on those parameters

void Sphere::RenderSphere(float radius, int segments)
{
	// setting initial values of 
	// longs and lats to get first point on sphere

	longs = 0;
	lats = 0;

	// keeping theta and delta as set values throughout the calculations

	theta = (2 * pi) / segments;
	delta = pi / segments;

	glBegin(GL_QUADS);

	// nested for loops, controlling num of quads / resolution
	// within one full circle from passed in parameters

	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			// set first normal, tex coord and vertice values of quad 
			// into respective variables

			vx = (radius * cos(lats))*sin(longs);
			vy = radius * cos(longs);
			vz = (radius * sin(lats)) * sin(longs);

			uCoord = ((float)j / segments);
			vCoord = ((float)i / segments);

			// placing variable values into each function

			glTexCoord2f(uCoord, vCoord);
			glNormal3f(vx, vy, vz);
			glVertex3f(vx, vy, vz);

			// set second normal, tex coord and vertice values of quad
			// into respective variables
			
			vx = (radius * cos(lats+theta)) * sin(longs);
			vy = radius * cos(longs);
			vz = (radius * sin(lats+theta)) * sin(longs);

			uCoord = ((float)(j+1) / segments);
			vCoord = ((float)i / segments);

			// placing variable values into each function

			glTexCoord2f(uCoord, vCoord);
			glNormal3f(vx, vy, vz);
			glVertex3f(vx, vy, vz);

			// set third normal, tex coord and vertice values of quad
			// into respective variables

			vx = (radius * cos(lats + theta)) * sin(longs + delta);
			vy = radius * cos(longs + delta);
			vz = (radius * sin(lats + theta)) * sin(longs + delta);


			uCoord = ((float)(j + 1) / segments);
			vCoord = ((float)(i + 1) / segments);

			// placing variable values into each function
			 
			glTexCoord2f(uCoord, vCoord);
			glNormal3f(vx, vy, vz);
			glVertex3f(vx, vy, vz);

			// set final normal, tex coord and vertice values of quad
			// into respective variables

			vx = (radius * cos(lats)) * sin(longs + delta);
			vy = radius * cos(longs + delta);
			vz = (radius * sin(lats)) * sin(longs + delta);


			uCoord = ((float)j  / segments);
			vCoord = ((float)(i + 1) / segments);

			// placing variable values into each function

			glTexCoord2f(uCoord, vCoord);
			glNormal3f(vx, vy, vz);
			glVertex3f(vx, vy, vz);

			// increase the angle on the latitude

			lats += theta;
		}

		// increase the angle on the longitude

		longs += delta;

	}

	glEnd();
}