#include "shape.h"


extern float verts[] = {	-1.0, 1.0, -1.0,			// Vertex #0
							-1.0, -1.0, -1.0,		// Vertex #1
							1.0,  -1.0, -1.0,		// Vertex #2
							1.0,  1.0, -1.0,			// Vertex #3

							-1.0, 1.0, 1.0,	// v4
							-1.0, 1.0, -1.0,		// v5
							1.0, 1.0, -1.0,		// v6
							1.0, 1.0, 1.0,		// v7

							-1.0, 1.0, 1.0,		// v8
							-1.0, -1.0, 1.0,		// v9
							-1.0, -1.0, -1.0,		// v10
							-1.0, 1.0, -1.0,		// v11

							1.0, 1.0, -1.0,		// v12
							1.0, -1.0, -1.0,		// v13
							1.0, -1.0, 1.0,		// v14
							1.0, 1.0, 1.0,		// v15

							-1.0, -1.0, -1.0,		// v16
							-1.0, -1.0, 1.0,		// v17
							1.0, -1.0, 1.0,		// v18
							1.0, -1.0, -1.0,		// v19

							1.0, 1.0, 1.0,		// v20
							1.0, -1.0, 1.0,		// v21
							-1.0, -1.0, 1.0,		// v22
							-1.0, 1.0, 1.0		// v23

						};

extern float norms[] = { 0.0, 0.0, -1.0,		//0
						0.0, 0.0, -1.0,		//1
 						0.0, 0.0, -1.0,		//2
						0.0, 0.0, -1.0,		//3

						0.0, 1.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 1.0, 0.0,
						0.0, 1.0, 0.0,

						-1.0, 0.0, 0.0,
						-1.0, 0.0, 0.0,
						-1.0, 0.0, 0.0,
						-1.0, 0.0, 0.0,

						1.0, 0.0, 0.0,
						1.0, 0.0, 0.0,
						1.0, 0.0, 0.0,
						1.0, 0.0, 0.0,

						0.0, -1.0, 0.0,
						0.0, -1.0, 0.0,
						0.0, -1.0, 0.0,
						0.0, -1.0, 0.0,

						0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,
						};		


extern float texcoords[]= {	0.0, 0.0, 		//0
							0.0, 1.0, 		//1
 							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
							};

extern GLubyte indices[] = {0,1,2,3,
							4,5,6,7,
							8,9,10,11,
							12,13,14,15,
							16,17,18,19,
							20,21,22,23
							};

void Shape::render3()
{
	// enables client states to retrieve info
	// from each of the arrays to then render to scene
	// using glDrawElements()

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}


