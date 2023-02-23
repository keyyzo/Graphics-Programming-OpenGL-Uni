#include "Cube.h"

// plane constructor setting initial values

Cube::Cube()
{
	// initialising texture coordinates

	uC = 0;
	vC = 0;

	// initialising normals and vertice values

	nx = 0, ny = 0, nz = 0;
	vx = 0, vy = 0, vz = 0;
}

//	initialising function calculating each vertice
// normal and texture coordinate for each number of quads
// controlled by a passed in parameter

void Cube::CalculateCube(int segments)
{	
	// nested for loops, each controlling width and heigh
	// of the plane from passed in parameter

	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			// calculates bottom left vertice, normal and texture coord
			// for each quad

			uC = (float)j / segments; vC = (float)i / segments;
			nx = 0; ny = 0; nz = 1;
			vx = j; vy = i; vz = 0;

			// store texture coords into texture vector

			tex.push_back(uC);
			tex.push_back(vC);

			// store normal coords into normal vector

			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);

			// store vertice coords into vertice vector

			verts.push_back(vx);
			verts.push_back(vy);
			verts.push_back(vz);

			// calculates bottom right vertice, normal and texture coord
			// for each quad

			uC = (float)(j+1) / segments; vC = (float)i / segments;
			nx = 0; ny = 0; nz = 1;
			vx = (j+1); vy = i; vz = 0;

			// store texture coords into texture vector

			tex.push_back(uC);
			tex.push_back(vC);

			// store normal coords into normal vector

			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);

			// store vertice coords into vertice vector

			verts.push_back(vx);
			verts.push_back(vy);
			verts.push_back(vz);

			// calculates top right vertice, normal and texture coord
			// for each quad

			uC = (float)(j+1) / segments; vC = (float)(i+1) / segments;
			nx = 0; ny = 0; nz = 1;
			vx = (j+1); vy = (i+1); vz = 0;

			// store texture coords into texture vector

			tex.push_back(uC);
			tex.push_back(vC);

			// store normal coords into normal vector

			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);

			// store vertice coords into vertice vector

			verts.push_back(vx);
			verts.push_back(vy);
			verts.push_back(vz);

			// calculates top left vertice, normal and texture coord
			// for each quad

			uC = (float)j / segments; vC = (float)(i + 1) / segments;
			nx = 0; ny = 0; nz = 1;
			vx = j; vy = (i+1); vz = 0;

			// store texture coords into texture vector

			tex.push_back(uC);
			tex.push_back(vC);

			// store normal coords into normal vector

			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);

			// store vertice coords into vertice vector

			verts.push_back(vx);
			verts.push_back(vy);
			verts.push_back(vz);

		}
	}
}

// initialises render function to render the plane to the scene

void Cube::RenderCube()
{		
	// enabling client states to obtain the data of the plane
	// stored in each vector 

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glTexCoordPointer(2, GL_FLOAT, 0, tex.data());

	// draws the plane to the scene once the functions called
	// uses dereferencing method 2

	glDrawArrays(GL_QUADS, 0, verts.size() / 3);

	// disable client states

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}