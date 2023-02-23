// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H
#pragma warning(disable:4996)

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include "Camera.h"
#include "Cylinder.h"
#include "Disc.h"
#include "Model.h"
#include "Shape.h"
#include "Sphere.h"
#include "Cube.h"
#include "Shadow.h"
#include "RatchetMove.h"
#include <vector>


class Scene{

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

	// calls skybox around the camera
	void renderSkybox();

protected:
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions
	

	// For access to user input.
	Input* input;
		
	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	// displaying the current camera in use
	// camera controls (if any at the time)
	// ratchet controls and wireframe button
	char cameraControls[120];
	char cameraChoices[80];
	char ratchetControls[120];
	char wireframeText[60];

	// all texture variables

	GLuint christmasCubeTex;
	GLuint sceneFloor;
	GLuint skyboxTexture;
	GLuint christmasBallTex;
	GLuint christmasCylinderTex;
	GLuint sunTexture;
	GLuint targetTex;

	// shadow object / variables

	Shadow treeArea;			// tree area shadowing 
	float treeShadow[16];
	
	Shadow crashArea;			// crash area shadowing 
	float crashShadow[16];

	// Shapes / objects around tree area

	Model tree;					// external model
	Shape cube;					// rendered in by an indice vertex array
	Sphere christmasBall;		// rendered in by procedural generation
	Cylinder christmasCylinder;	// rendered in by procedural generation

	// Plane objects
	// The plane is both saved to a vertex array
	// and is procedurally generated within the scene

	Cube test, floor;

	// Sun object

	Sphere sun;					// rendered in by procedural generation

	
	// Rayman area objects 

	Model rayman;				// external model
	Sphere lum;					// rendered in by procedural generation
	Disc target;				// rendered in by procedural generation
	
	// Crash area objects
	// All external models

	Model crash, wumpa, uka;

	// Ratchet object - controllable
	RatchetMove ratchet;		// external model

	// Camera objects / variables

	Camera camera;			// cam 1
	Camera topview;			// cam 2	// four different cameras
	Camera overview;		// cam 3
	Camera panAroundView;	// cam 4

	bool inWindow;				// allows for mouse control outside window when in free roam camera
	bool wireframeMode;
	bool firstCV, secondCV, thirdCV, fourthCV;	// controls which camera is in use
	bool isFirstFrame = true;
	float centreX, centreY, distanceMovedX, distanceMovedY;
	int cameraNum;

	// all variables that are related
	// to a rotating object / camera

	float wumpaSpeed, sunSpeed, sunSpeed2;
	float wumpaRotate, sunRotate, sunRotate2;
	float panRotate, panSpeed;

	//	colour variables controlling
	// the rotating colours on the light
	// at the crash area

	float color1, color2, color3;
	bool color1Done, color2Done, color3Done;
	bool c1Live, c2Live, c3Live;

	// all variables are linked to the lums that rayman throws
	// controls the dimming / reglowing

	float lightVal, lightValDT, lightValchange = 0.025f;
	bool lightLimit;

	// controls the positioning

	float lumPos, lumPos2, lumPos3;
	bool lumPosReach, lumPosReach2, lumPosReach3;

	// controls number of quads within the plane function

	float segmentsPlane;

};

#endif