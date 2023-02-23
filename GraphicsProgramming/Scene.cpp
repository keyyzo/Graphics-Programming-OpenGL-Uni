#include "Scene.h"

// Scene constructor, initilises OpenGL
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	

	// Other OpenGL / render setting should be applied here.
	

	// Initialise scene variables

	// num of quads on planes

	segmentsPlane = 300;

	// lum light and position values 

	lightVal = 0.1f;
	lightLimit = false;
	lumPos = 5, lumPos2 = 15, lumPos3 = 25;
	lumPosReach = false, lumPosReach2 = false, lumPosReach3 = false;

	// all camera variables

	inWindow = false;
	wireframeMode = false;
	firstCV = true;
	secondCV = false;
	thirdCV = false;
	fourthCV = false;

	glutWarpPointer(centreX, centreY);

	// variables affected by movement speed

	wumpaSpeed = 75.0f;
	sunSpeed = 20.0f, sunSpeed2 = 10.0f;
	panSpeed = 30.0f;

	// variables controlling the crash area light colour

	color1 = 0.00f, color2 = 0.00f, color3 = 0.00f;
	color1Done = false, color2Done = false, color3Done = false;
	
	// initiliasing all textures used on objects not loaded in 
	// using the model class

	sceneFloor = SOIL_load_OGL_texture
	(
		"gfx/snow.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	christmasCubeTex = SOIL_load_OGL_texture
	(
		"gfx/giftwrapOne.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	christmasBallTex = SOIL_load_OGL_texture
	(
		"gfx/football.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	christmasCylinderTex = SOIL_load_OGL_texture
	(
		"gfx/giftwrapThree.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);


	skyboxTexture = SOIL_load_OGL_texture
	(
		"gfx/skyboxv7.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	sunTexture = SOIL_load_OGL_texture
	(
		"gfx/sun.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	targetTex = SOIL_load_OGL_texture
	(
		"gfx/target.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	// initialising planes used within scene
	// and setting the num of quads use within them

	test.CalculateCube(20);
	floor.CalculateCube(300);

	// loading all external model files and their respective texture files

	rayman.load("models/Rayman3model.obj", "models/rayman.png");
	tree.load("models/ChristmasTree.obj", "models/Handle1Tex.png");
	crash.load("models/crashN.obj", "models/Crash.png");
	wumpa.load("models/Wumpa.obj","models/mtl0.png");
	uka.load("models/mask.obj","models/mask.png");
	ratchet.load("models/ratchetN2.obj", "models/Ratchet_D.png");
}


// handles user input and updates variable values within the scene

void Scene::handleInput(float dt)
{
	// for working out centre of the screen

	centreX = width / 2;
	centreY = height / 2;

	// checking for first frame and help lock
	// mouse pos in centre of the screen

	if (isFirstFrame == true) {
		isFirstFrame = false;
	}
	else 
	{

		distanceMovedX = input->getMouseX() - centreX;
		distanceMovedY = input->getMouseY() - centreY;
	}

	// allows for releasing the mouse pos from centre of screen
	// and stopping mouse movement from affecting the scene

	if (input->isKeyDown('v') && !inWindow)
	{
		input->SetKeyUp('v');

		inWindow = true;
	}

	else if (input->isKeyDown('v') && inWindow)
	{
		input->SetKeyUp('v');

		inWindow = false;

	}


	// free roam camera controls and updates

	if (firstCV)
	{
		// setting movement controls to specific keys

		if (input->isKeyDown('w'))
		{
			camera.moveForward(dt);
		}

		if (input->isKeyDown('s'))
		{
			camera.moveBackwards(dt);
		}

		if (input->isKeyDown('a'))
		{
			camera.moveLeft(dt);
		}

		if (input->isKeyDown('d'))
		{
			camera.moveRight(dt);
		}

		if (input->isKeyDown('q'))
		{
			camera.moveUp(dt);
		}

		if (input->isKeyDown('e'))
		{
			camera.moveDown(dt);
		}

		// will check for mouse is enabled to centre screen
		// if not will not update mouse pos in screen

		if (!inWindow)
		{
			if (input->getMouseX())
			{
				camera.changeYaw(distanceMovedX);
			}

			if (input->getMouseY())
			{
				camera.changePitch(-distanceMovedY);
			}

			glutWarpPointer(centreX, centreY);
			input->setMousePos(centreX, centreY);
		}

		// updates values within the camera

		camera.Update(dt);
	}

	// overview camera controls and updates

	if (thirdCV)
	{
		// same as free roam cam, controls updates to
		// mouse pos if not locked to centre of the screen

		if (!inWindow)
		{
			if (input->getMouseX())
			{
				overview.changeYaw(distanceMovedX);
			}

			if (input->getMouseY())
			{
				overview.changePitch(-distanceMovedY);
			}

			glutWarpPointer(centreX, centreY);
			input->setMousePos(centreX, centreY);
		}

		// updates values within the camera

		overview.Update(dt);

	}

	// setting up button to activate / deactivate wireframe mode

	if (input->isKeyDown('/') && !wireframeMode)
	{
		input->SetKeyUp('/');
		wireframeMode = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	else if (input->isKeyDown('/') && wireframeMode)
	{
		input->SetKeyUp('/');
		wireframeMode = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// pressing the num 1 key activates free roam camera

	if (input->isKeyDown('1') && !firstCV)
	{
		input->SetKeyUp('1');
		firstCV = true;
		secondCV = false;
		thirdCV = false;
		fourthCV = false;
	}

	// pressing the num 2 key activates topdown view camera

	if (input->isKeyDown('2') && !secondCV)
	{
		input->SetKeyUp('2');
		firstCV = false;
		secondCV = true;
		thirdCV = false;
		fourthCV = false;
	}

	// pressing the num 3 key activates overview camera

	if (input->isKeyDown('3') && !thirdCV)
	{
		input->SetKeyUp('3');
		firstCV = false;
		secondCV = false;
		thirdCV = true;
		fourthCV = false;
	}

	// pressing the num 4 key activates pan around scene camera

	if (input->isKeyDown('4') && !fourthCV)
	{
		input->SetKeyUp('4');
		firstCV = false;
		secondCV = false;
		thirdCV = false;
		fourthCV = true;
	}

	// setting up ratchet controls to specific keys

	if (input->isKeyDown('i'))
	{
		ratchet.moveForward(dt);
	}

	if (input->isKeyDown('k'))
	{
		ratchet.moveBackwards(dt);
	}

	if (input->isKeyDown('j'))
	{
		ratchet.rotateLeft(dt);
	}

	if (input->isKeyDown('l'))
	{
		ratchet.rotateRight(dt);
	}

	if (input->isKeyDown('u'))
	{
		ratchet.moveUp(dt);
	}

	if (input->isKeyDown('o'))
	{
		ratchet.moveDown(dt);
	}

	// updates variables within the ratchet class

	ratchet.Update(dt);
}

// updating variables within the function affecting
// the scene each frame

void Scene::update(float dt)
{
	// all rotation variables within the scene

	wumpaRotate += wumpaSpeed * dt;
	sunRotate += sunSpeed * dt;
	sunRotate2 += sunSpeed2 * dt;
	panRotate += panSpeed * dt;


	// controlling dim / glow of the lums

	if (lightVal >= 0.9)
	{
		lightLimit = true;
	}

	else if (lightVal <= 0.1)
	{
		lightLimit = false;
	}

	if (!lightLimit)
	{
		lightVal += lightValchange;
		
	}

	else if (lightLimit)
	{
		lightVal -= lightValchange;
	}


	// each lums change of position to hit
	// the target
	
	if (lumPos < 40)
	{
		lumPosReach = false;
	}

	else if (lumPos >= 40)
	{
		lumPosReach = true;
	}
								// lum one
	if (!lumPosReach)
	{
		lumPos += 0.2;
	}

	else if (lumPosReach)
	{
		lumPos = 0.5;
	}


	if (lumPos2 < 40)
	{
		lumPosReach2 = false;
	}

	else if (lumPos2 >= 40)
	{
		lumPosReach2 = true;
	}
								// lum two
	if (!lumPosReach2)
	{
		lumPos2 += 0.2;
	}

	else if (lumPosReach2)
	{
		lumPos2 = 0.5;
	}


	if (lumPos3 < 40)
	{
		lumPosReach3 = false;
	}

	else if (lumPos3 >= 40)
	{
		lumPosReach3 = true;
	}
								// lum three
	if (!lumPosReach3)
	{
		lumPos3 += 0.2;
	}

	else if (lumPosReach3)
	{
		lumPos3 = 0.5;
	}

	// loops through each colour available
	// constantly as the scene is running
	// affecting the colour of the light within
	// the crash area

	if (color1 >= 0.0 || color3Done == true)
	{
		c1Live = true;
	}

	else if (color1 < 0.0)
	{
		c1Live = false;
		color1Done = false;
	}

	if (color1 >= 2.0)
	{
		color1Done = true;						// changing red value
	}

	if (c1Live && !color1Done)
	{
		color1 += 0.05;
	}

	else if (c1Live && color1Done)
	{
		color1 -= 0.05;
	}


	if (color2 >= 0.0 || color1Done == true)
	{
		c2Live = true;
	}

	else if (color2 < 0.0)
	{
		c2Live = false;
		color2Done = false;
	}

	if (color2 >= 2.0)
	{
		color2Done = true;						// changing green value
	}

	if (c2Live && !color2Done && color1Done)
	{
		color2 += 0.05;
	}

	else if (c2Live && color2Done)
	{
		color2 -= 0.05;
	}


	if (color3 >= 0.0 || color2Done == true)
	{
		c3Live = true;
	}

	else if (color3 <= 0.0)
	{
		c3Live = false;
		color3Done = false;
	}

	if (color3 >= 2.0)
	{
		color3Done = true;						// changing blue value
	}

	if (c3Live && !color3Done && color2Done)
	{
		color3 += 0.05;
	}

	else if (c3Live && color3Done)
	{
		color3 -= 0.05;
	}

	
	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera

	// free roam camera

	if (firstCV)
	{
		gluLookAt(camera.getPositionX(), camera.getPositionY(), camera.getPositionZ(), camera.getLookAtX(), camera.getLookAtY(), camera.getLookAtZ(), camera.getUpX(), camera.getUpY(), camera.getUpZ());
		cameraNum = 1;
	}

	// topdown view of the scene - no control

	else if (secondCV)
	{
		topview.setPositionX(0),topview.setPositionY(120),topview.setPositionZ(0);
		gluLookAt(topview.getPositionX(), topview.getPositionY(), topview.getPositionZ(), 0, 0, 1, 0, 0, -1);
		cameraNum = 2;
	}

	// corner view of the scene - control only lookat

	else if (thirdCV)
	{
		overview.setPositionX(-60), overview.setPositionY(70), overview.setPositionZ(60);
		gluLookAt(overview.getPositionX(), overview.getPositionY(), overview.getPositionZ(), overview.getLookAtX(), overview.getLookAtY(), overview.getLookAtZ(), 0, 1, 0);
		cameraNum = 3;
	}

	// 0,-35,0

	// rotating camera around the scene - no control

	else if (fourthCV)
	{
		panAroundView.setPositionX(0), panAroundView.setPositionY(20), panAroundView.setPositionZ(90);
		gluLookAt(panAroundView.getPositionX(), panAroundView.getPositionY(), panAroundView.getPositionZ(), 0, 0, 0, 0, 1, 0);
		glRotatef(-panRotate, 0, 1, 0);
		cameraNum = 4;
	}
	
	
	// Render geometry/scene here -------------------------------------

	// skybox rendered around camera
	renderSkybox();

	// christmas tree area - lighting
	glPushMatrix();

		GLfloat Light_Diffuse[] = { 0.7f, 0.4f, 0.0f, 1.0f };
		GLfloat Light_Position[] = { -30.0f, 90.0f, -30.0f, 1.0f };
		GLfloat Spot_Direction[] = { 0.0f, -1.0f, 0.0f };
		GLfloat Light_ConstantA = { 1.0 };
		GLfloat Light_LinearA = { 0.005 };
		GLfloat Light_QuadraticA = { 0.00005 };

		glLightfv(GL_LIGHT0, GL_DIFFUSE, Light_Diffuse);
		glLightfv(GL_LIGHT0, GL_POSITION, Light_Position);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0f);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Spot_Direction);
		glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 55.0);

		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Light_ConstantA);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Light_LinearA);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Light_QuadraticA);

		glEnable(GL_LIGHT0);

	glPopMatrix();

	// crash area - lighting

	glPushMatrix();


		GLfloat Crash_Diffuse[] = { color1,color2,color3,1.0 };			// uses passed in variables being updated constantly
		GLfloat Crash_Position[] = { 60.0f, 40.0f, 60.0f, 1.0f };		// to imitate looping through each colour 
		GLfloat Crash_Direction[] = { -1.0f, -1.5f,-1.0f };
		GLfloat Crash_ConstantA = { 1.0 };
		GLfloat Crash_LinearA = { 0.05 };
		GLfloat Crash_QuadraticA = { 0.0005 };

		glLightfv(GL_LIGHT5, GL_DIFFUSE, Crash_Diffuse);
		glLightfv(GL_LIGHT5, GL_POSITION, Crash_Position);
		glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 40.0f);
		glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, Crash_Direction);
		glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 85.0);

		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, Crash_ConstantA);
		glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, Crash_LinearA);
		glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, Crash_QuadraticA);

		glEnable(GL_LIGHT5);

	glPopMatrix();

	// bottom plane - floor
	// plane is procedurally generated
	// saved to and loaded from a vertex array into scene

	glPushMatrix();

		glEnable(GL_CULL_FACE);
		//glBindTexture(GL_TEXTURE_2D, sceneFloor);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glScalef(0.3333, 0.3333, 0.3333);
		glTranslatef(-(segmentsPlane / 2), 0, segmentsPlane / 2);
		glRotatef(-90, 1, 0, 0);

		glColor3f(1.0, 1.0, 1.0);

		floor.RenderCube();
		
		glBindTexture(GL_TEXTURE_2D, NULL);
		glDisable(GL_CULL_FACE);

	glPopMatrix();

	// small plane used within generating shadows on the scene

	GLfloat floorVerts[] = { -1,0,-1,
								-1,0,1,
								1,0,1,
								1,0,-1 };

	// crash area - shadowing

	crashArea.generateShadowMatrix(crashShadow, Crash_Position, floorVerts);

	glPushMatrix();

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glColor3f(0.2, 0.2, 0.2);

		glPushMatrix();

			// calculating the shadowed objects 
			// to be displayed

			glMultMatrixf((GLfloat*)crashShadow);

			glPushMatrix();

				// crash shadow	

				glTranslatef(30, 0, 15);
				glScalef(0.1, 0.1, 0.1);
				crash.render();

				// wumpa shadows

				glPushMatrix();

					glTranslatef(0, 25, 60);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				glPushMatrix();

					glTranslatef(0, 25, 100);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				glPushMatrix();

					glTranslatef(0, 25, 140);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				glPushMatrix();

					glTranslatef(0, 25, 180);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				glPushMatrix();
		
					glTranslatef(0, 25, 220);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				glPushMatrix();

					glTranslatef(0, 25, 260);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				glPushMatrix();

					glTranslatef(40, 25, 220);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				glPushMatrix();

					glTranslatef(-40, 25, 220);
					glRotatef(wumpaRotate, 0, 1, 0);
					wumpa.render();

				glPopMatrix();

				// uka uka shadow

				glPushMatrix();

					glTranslatef(0, 50, 320);
					glRotatef(180, 0, 1, 0);
					uka.render();

				glPopMatrix();



			glPopMatrix();

		glPopMatrix();

		glColor3f(1, 1, 1);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

	glPopMatrix();

	// christmas tree area - shadowing

	treeArea.generateShadowMatrix(treeShadow, Light_Position, floorVerts);

	glPushMatrix();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.1, 0.1, 0.1);

		glPushMatrix();
	
			// calculating the shadowed objects 
			// to be displayed

			glMultMatrixf((GLfloat*)treeShadow);

			// christmas ball shadow

			glPushMatrix();
				glTranslatef(-15, 2, -30);
				christmasBall.RenderSphere(2, 30);
			glPopMatrix();

			// christmas cube shadow

			glPushMatrix();

				glScalef(2, 2, 2);
				glTranslatef(-10, 1, -20);
				cube.render3();
				
			glPopMatrix();

			//	christmas cylinder shadow

			glPushMatrix();

				glTranslatef(-38, 2, -20);
				glRotatef(55, 0, 1, 0);
				christmasCylinder.RenderCylinder(4, 40, 10);

			glPopMatrix();

		glPopMatrix();

	glColor3f(1, 1, 1);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

		// christmas ball object - procedurally generated sphere

		glPushMatrix();

			glEnable(GL_CULL_FACE);
			glBindTexture(GL_TEXTURE_2D, christmasBallTex);
			glTranslatef(-15, 2, -30);
			christmasBall.RenderSphere(2, 30);
			glBindTexture(GL_TEXTURE_2D, NULL);
			glDisable(GL_CULL_FACE);

		glPopMatrix();

		// christmas cube object - procedurally generated cube loaded from vertex array

		glPushMatrix();

			glBindTexture(GL_TEXTURE_2D, christmasCubeTex);
			glScalef(2, 2, 2);
			glTranslatef(-10, 1, -20);
			cube.render3();
			glBindTexture(GL_TEXTURE_2D, NULL);

		glPopMatrix();

		// christmas cylinder object - procedurally generated cylinder

		glPushMatrix();
			
			glBindTexture(GL_TEXTURE_2D, christmasCylinderTex);
			glTranslatef(-38, 2, -20);
			glRotatef(55, 0, 1, 0);
			christmasCylinder.RenderCylinder(4, 40, 10);
			glBindTexture(GL_TEXTURE_2D, NULL);

		glPopMatrix();


	glPopMatrix();

	// christmas tree - external model 
	glPushMatrix();

		glEnable(GL_CULL_FACE);
		glTranslatef(-30, 0, -30);
		glScalef(15, 15, 15);
		tree.render();
		glDisable(GL_CULL_FACE);

	glPopMatrix();


	// crash area

	glPushMatrix();

		// crash object - external model	

		glTranslatef(40, 0, 25);
		glScalef(0.1, 0.1, 0.1);
		crash.render();

		// wumpa objects - external model

		glPushMatrix();

			glTranslatef(0, 25, 60);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(0, 25, 100);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(0, 25, 140);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();
	
		glPushMatrix();

			glTranslatef(0, 25, 180);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(0, 25, 220);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(0, 25, 260);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(40, 25, 220);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(-40, 25, 220);
			glRotatef(wumpaRotate, 0, 1, 0);
			wumpa.render();

		glPopMatrix();

		// uka uka object - external model

		glPushMatrix();

			glTranslatef(0, 50, 320);
			glRotatef(180, 0, 1, 0);
			uka.render();

		glPopMatrix();

	glPopMatrix();

	// sun area 

	glPushMatrix();
		
		// sun object acts as a global ambient light source
		// giving the whole scene some ambient light

		GLfloat Sun_Ambient[] = { 0.45,0.45,0.45,1 };
		GLfloat Sun_Position[] = { 100,50,-150,1 };

		glLightfv(GL_LIGHT1, GL_AMBIENT, Sun_Ambient);
		glLightfv(GL_LIGHT1, GL_POSITION, Sun_Position);

		glEnable(GL_LIGHT1);

		glRotatef(sunRotate, 0, 1, 0);
		glPushMatrix();

		// sun object - procedurally generated sphere

			glEnable(GL_CULL_FACE);
			glBindTexture(GL_TEXTURE_2D, sunTexture);
			glTranslatef(100, 50, -150);
			glRotatef(sunRotate2, 0, 1, 0);
			sun.RenderSphere(20, 50);
			glBindTexture(GL_TEXTURE_2D, NULL);
			glDisable(GL_CULL_FACE);

		glPopMatrix();

	glPopMatrix();

	// Ratchet and clank - external model
	// created as a controllable / moveable object

	glPushMatrix();

		glTranslatef(-20, 2, 35);
		glScalef(0.4, 0.4, -0.4);

		glTranslatef(ratchet.getPositionX(), ratchet.getPositionY(), ratchet.getPositionZ());
		glRotatef(ratchet.getYaw(), 0, 1, 0);
		ratchet.render();

	glPopMatrix();

	// mirror - used to mirror the rayman area

	glPushMatrix();

		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDisable(GL_DEPTH_TEST);

		// wireframing the back of the quad
		// to stop mirror object from appearing at the back

		if (!wireframeMode)
		{
			glPolygonMode(GL_FRONT, GL_LINE);
		}
		
		// quad for mirror - hand drawn

		glBegin(GL_QUADS);

			glVertex3f(50, 20, 0);
			glVertex3f(50, 0, 0);
			glVertex3f(50, 0, -50);
			glVertex3f(50,20, -50);


		glEnd();

		if (!wireframeMode)
		{
			glPolygonMode(GL_FRONT, GL_FILL);
		}


		glEnable(GL_DEPTH_TEST);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

		glPushMatrix();

			// Rayman object - mirrored

			glScalef(-1, 1, 1);
			glTranslatef(-75, 0, -5);
			glRotatef(180, 0, 1, 0);
			glScalef(0.2, 0.2, 0.2);
			rayman.render();

			// lum objects - mirrored
			// lumPos and lightVal are constantly updating variables
			// for each light with their corresponding variable names ie lumPod, lumPos2, lightVal3 etc
			// affecting the dim / glow of the light and positioning 
			// of the object

			glPushMatrix();

				glScalef(5, 5, 5);

				// lum one light - mirrored

				GLfloat Lum_Emission[] = { 0.1f, 0.3f,0.9f, 0.0f };
				GLfloat Lum_Diffuse[] = { 0.1,0.3,0.9,1 };
				GLfloat Lum_Position[] = { 0,5,lumPos,1 };
				GLfloat Lum_Spot[] = { 0.0,-1.0,0.0 };

				GLfloat Lum_ConstantA = { 1.0 };
				GLfloat Lum_LinearA = { 0.35 };
				GLfloat Lum_QuadraticA = { lightVal };


				glLightfv(GL_LIGHT2, GL_DIFFUSE, Lum_Diffuse);
				glLightfv(GL_LIGHT2, GL_POSITION, Lum_Position);
				glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Lum_Spot);
				glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 15.0);

				glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, Lum_ConstantA);
				glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, Lum_LinearA);
				glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, Lum_QuadraticA);


				glEnable(GL_LIGHT2);

				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission);

				glColor3f(0.1, 0.5, 0.9);

				glTranslatef(0, 5, lumPos);
				glScalef(0.5, 0.5, 0.5);
				lum.RenderSphere(1, 30);
				Lum_Emission[0] = 0;
				Lum_Emission[1] = 0;
				Lum_Emission[2] = 0;
				Lum_Emission[3] = 0;
				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission);

				glColor3f(1, 1, 1);

			glPopMatrix();

			glPushMatrix();

				glScalef(5, 5, 5);

				// lum two light - mirrored

				GLfloat Lum_Emission2[] = { 0.1f, 0.3f, 0.9f, 0.0f };
				GLfloat Lum_Diffuse2[] = { 0.1,0.3,0.9,1 };
				GLfloat Lum_Position2[] = { 0,5,lumPos2,1 };
				GLfloat Lum_Spot2[] = { 0.0,-1.0,0.0 };
				GLfloat Lum_ConstantA2 = { 1 };
				GLfloat Lum_LinearA2 = { 0.35 };
				GLfloat Lum_QuadraticA2 = { lightVal };

				glLightfv(GL_LIGHT3, GL_DIFFUSE, Lum_Diffuse2);
				glLightfv(GL_LIGHT3, GL_POSITION, Lum_Position2);
				glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, Lum_Spot2);
				glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 15.0);

				glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, Lum_ConstantA2);
				glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, Lum_LinearA2);
				glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, Lum_QuadraticA2);

				glEnable(GL_LIGHT3);

				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission2);

				glColor3f(0.1, 0.5, 0.9);

				glTranslatef(0, 5, lumPos2);
				glScalef(0.5, 0.5, 0.5);
				lum.RenderSphere(1, 30);
				Lum_Emission2[0] = 0;
				Lum_Emission2[1] = 0;
				Lum_Emission2[2] = 0;
				Lum_Emission2[3] = 0;
				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission2);

				glColor3f(1, 1, 1);

			glPopMatrix();

			glPushMatrix();

				glScalef(5, 5, 5);

				// lum three light - mirrored

				GLfloat Lum_Emission3[] = { 0.1f, 0.3f, 0.9f, 0.0f };
				GLfloat Lum_Diffuse3[] = { 0.1,0.3,0.9,1 };
				GLfloat Lum_Position3[] = { 0,5,lumPos3,1 };
				GLfloat Lum_Spot3[] = { 0.0,-1.0,0.0 };
				GLfloat Lum_ConstantA3 = { 1 };
				GLfloat Lum_LinearA3 = { 0.35 };
				GLfloat Lum_QuadraticA3 = { lightVal };

				glLightfv(GL_LIGHT4, GL_DIFFUSE, Lum_Diffuse3);
				glLightfv(GL_LIGHT4, GL_POSITION, Lum_Position3);
				glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 90);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, Lum_Spot3);
				glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);

				glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, Lum_ConstantA3);
				glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, Lum_LinearA3);
				glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, Lum_QuadraticA3);

				glEnable(GL_LIGHT4);

				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission3);

				glColor3f(0.1, 0.5, 0.9);

				glTranslatef(0, 5, lumPos3);
				glScalef(0.5, 0.5, 0.5);
				lum.RenderSphere(1, 30);
				Lum_Emission3[0] = 0;
				Lum_Emission3[1] = 0;
				Lum_Emission3[2] = 0;
				Lum_Emission3[3] = 0;
				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission3);

				glColor3f(1, 1, 1);

			glPopMatrix();

			// disc object - mirrored

			glPushMatrix();

				glBindTexture(GL_TEXTURE_2D, targetTex);
				glScalef(5, 5, 5);
				glTranslatef(0, 5, 40);
				target.RenderDisc(5, 30);
				glBindTexture(GL_TEXTURE_2D, NULL);

			glPopMatrix();

		glPopMatrix();

		glPushMatrix();

			//	bottom floor plane - mirrored

			glEnable(GL_CULL_FACE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glScalef(0.3333, 0.3333, 0.3333);
			glTranslatef(-(segmentsPlane / 2), 0, segmentsPlane / 2);
			glTranslatef(segmentsPlane, 0, 0);
			glRotatef(-90, 1, 0, 0);

			glColor3f(1.0, 1.0, 1.0);

			floor.RenderCube();
			
			glDisable(GL_CULL_FACE);
		glPopMatrix();

		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glColor4f(0.8, 0.8, 1.0, 0.8);

		// quad for mirror - hand drawn
		// front of mirror to show reflected items 

		glBegin(GL_QUADS);

			glVertex3f(50, 20, 0);
			glVertex3f(50, 0, 0);
			glVertex3f(50, 0, -50);
			glVertex3f(50, 20, -50);

		glEnd();

		glColor3f(1, 1, 1);


		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);

		glPushMatrix();

			// rayman object - external model

			glTranslatef(25, 0, -5);
			glRotatef(180, 0, 1, 0);
			glScalef(0.2, 0.2, 0.2);
			rayman.render();

			// lum objects - procedurally generated spheres
			// lumPos and lightVal are constantly updating variables
			// for each light with their corresponding variable names ie lumPod, lumPos2, lightVal3 etc
			// affecting the dim / glow of the light and positioning 
			// of the object

			glPushMatrix();

				glScalef(5, 5, 5);

				// lum one light
				
				Lum_Emission[0] = 0.1f;
				Lum_Emission[1] = 0.3f;
				Lum_Emission[2] = 0.9f;
				Lum_Emission[3] = 0.0f;

				Lum_Diffuse[0] = 0.1f;
				Lum_Diffuse[1] = 0.3f;
				Lum_Diffuse[2] = 0.9f;
				Lum_Diffuse[3] = 0.0f;

				Lum_Position[0] = 0.0f;
				Lum_Position[1] = 5.0f;
				Lum_Position[2] = lumPos;
				Lum_Position[3] = 1.0f;

				Lum_Spot[0] = 0.0f;
				Lum_Spot[1] = -1.0f;
				Lum_Spot[2] = 0.0f;

				Lum_ConstantA = { 1.0 };
				Lum_LinearA = { 0.35 };
				Lum_QuadraticA = { lightVal };


				glLightfv(GL_LIGHT2, GL_DIFFUSE, Lum_Diffuse);
				glLightfv(GL_LIGHT2, GL_POSITION, Lum_Position);
				glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Lum_Spot);
				glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 15.0);

				glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, Lum_ConstantA);
				glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, Lum_LinearA);
				glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, Lum_QuadraticA);


				glEnable(GL_LIGHT2);

				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission);

				glColor3f(0.1, 0.5, 0.9);

				glTranslatef(0, 5, lumPos);
				glScalef(0.5, 0.5, 0.5);
				lum.RenderSphere(1, 30);
				Lum_Emission[0] = 0;
				Lum_Emission[1] = 0;
				Lum_Emission[2] = 0;
				Lum_Emission[3] = 0;
				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission);

				glColor3f(1, 1, 1);

			glPopMatrix();

			glPushMatrix();

				glScalef(5, 5, 5);

				// lum two light

				Lum_Emission2[0] = 0.1f;
				Lum_Emission2[1] = 0.3f;
				Lum_Emission2[2] = 0.9f;
				Lum_Emission2[3] = 0.0f;

				Lum_Diffuse2[0] = 0.1f;
				Lum_Diffuse2[1] = 0.3f;
				Lum_Diffuse2[2] = 0.9f;
				Lum_Diffuse2[3] = 0.0f;

				Lum_Position2[0] = 0.0f;
				Lum_Position2[1] = 5.0f;
				Lum_Position2[2] = lumPos2;
				Lum_Position2[3] = 1.0f;

				Lum_Spot2[0] = 0.0f;
				Lum_Spot2[1] = -1.0f;
				Lum_Spot2[2] = 0.0f;

				Lum_ConstantA2 = { 1.0 };
				Lum_LinearA2 = { 0.35 };
				Lum_QuadraticA2 = { lightVal };

				glLightfv(GL_LIGHT3, GL_DIFFUSE, Lum_Diffuse2);
				glLightfv(GL_LIGHT3, GL_POSITION, Lum_Position2);
				glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, Lum_Spot2);
				glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 15.0);

				glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, Lum_ConstantA2);
				glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, Lum_LinearA2);
				glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, Lum_QuadraticA2);

				glEnable(GL_LIGHT3);

				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission2);

				glColor3f(0.1, 0.5, 0.9);

				glTranslatef(0, 5, lumPos2);
				glScalef(0.5, 0.5, 0.5);
				lum.RenderSphere(1, 30);
				Lum_Emission2[0] = 0;
				Lum_Emission2[1] = 0;
				Lum_Emission2[2] = 0;
				Lum_Emission2[3] = 0;
				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission2);

				glColor3f(1, 1, 1);

			glPopMatrix();

			glPushMatrix();

				glScalef(5, 5, 5);

				// lum three light

				Lum_Emission3[0] = 0.1f;
				Lum_Emission3[1] = 0.3f;
				Lum_Emission3[2] = 0.9f;
				Lum_Emission3[3] = 0.0f;

				Lum_Diffuse3[0] = 0.1f;
				Lum_Diffuse3[1] = 0.3f;
				Lum_Diffuse3[2] = 0.9f;
				Lum_Diffuse3[3] = 0.0f;

				Lum_Position3[0] = 0.0f;
				Lum_Position3[1] = 5.0f;
				Lum_Position3[2] = lumPos3;
				Lum_Position3[3] = 1.0f;

				Lum_Spot3[0] = 0.0f;
				Lum_Spot3[1] = -1.0f;
				Lum_Spot3[2] = 0.0f;

				Lum_ConstantA3 = { 1.0 };
				Lum_LinearA3 = { 0.35 };
				Lum_QuadraticA3 = { lightVal };


				glLightfv(GL_LIGHT4, GL_DIFFUSE, Lum_Diffuse3);
				glLightfv(GL_LIGHT4, GL_POSITION, Lum_Position3);
				glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 90);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, Lum_Spot3);
				glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0);

				glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, Lum_ConstantA3);
				glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, Lum_LinearA3);
				glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, Lum_QuadraticA3);

				glEnable(GL_LIGHT4);

				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission3);

				glColor3f(0.1, 0.5, 0.9);

				glTranslatef(0, 5, lumPos3);
				glScalef(0.5, 0.5, 0.5);
				lum.RenderSphere(1, 30);
				Lum_Emission3[0] = 0;
				Lum_Emission3[1] = 0;
				Lum_Emission3[2] = 0;
				Lum_Emission3[3] = 0;
				glMaterialfv(GL_FRONT, GL_EMISSION, Lum_Emission3);

				glColor3f(1, 1, 1);

			glPopMatrix();

			// disc object - procedurally generated disc

			glPushMatrix();

				glBindTexture(GL_TEXTURE_2D, targetTex);
				glScalef(5, 5, 5);
				glTranslatef(0, 5, 40);
				target.RenderDisc(5, 30);
				glBindTexture(GL_TEXTURE_2D, NULL);

			glPopMatrix();

		glPopMatrix();

	glPopMatrix();

	// glass window object - plane
	// plane is procedurally generated
	// saved to and loaded from a vertex array into scene

	glPushMatrix();

		glEnable(GL_BLEND);
		glScalef(1, 1, 5);
		glRotatef(90, 0, 1, 0);
		glTranslatef(-10, 0, 0);
		glColor4f(0.1, 0.1, 0.4, 0.25);
		test.RenderCube();
		glDisable(GL_BLEND);
		glColor3f(1, 1, 1);

	glPopMatrix();

	// End render geometry --------------------------------------

	// Render text, should be last object rendered.

	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 60.0f;
	nearPlane = 0.1f;
	farPlane = 500.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	
}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	glDisable(GL_LIGHTING);

	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());

	// Displays control options for cameras and which one is currently in use
	sprintf_s(cameraChoices, "Press numbers 1-4 to change camera types | Camera in use: %i",cameraNum);

	// Displays all controls for the moveable object ratchet
	sprintf_s(ratchetControls, "Control Ratchet! | I - Forward | K - Backwards | J - Rotate left | L - Rotate right | U - Up | O - Down");

	// Displays which button to press to activate wireframe mode
	sprintf_s(wireframeText, "Press / to toggle Wireframe mode on or off");

	// Displays certain message to user depending on which camera is active 
	// to show which camera it is and if there are controls / what controls are available

	if (firstCV)
	{
		sprintf_s(cameraControls, "Free roam camera | W - Forward | S - Backwards | A - Left | D - Right | Q - Up | E - Down | Aim with mouse");
	}

	if (secondCV)
	{
		sprintf_s(cameraControls, "Topdown view | Fixed camera");
	}

	if (thirdCV)  
	{
		sprintf_s(cameraControls, "Overview | Aim with mouse");
	}

	if (fourthCV)
	{
		sprintf_s(cameraControls, "Rotate around scene | No controls");
	}
	
	// positions and renders all text values within the scene

	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.92f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.88f, 1.f, 0.f, 0.f, cameraChoices);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, cameraControls);
	displayText(-1.f, 0.80f, 1.f, 0.f, 0.f, ratchetControls);
	displayText(-1.f, 0.76f, 1.f, 0.f, 0.f, wireframeText);

	glEnable(GL_LIGHTING);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

// positions, updates and renders skybox to the scene

void Scene::renderSkybox()
{
	glPushMatrix();

	glBindTexture(GL_TEXTURE_2D, skyboxTexture);

	// wraps the skybox around each camera
	// changes position depending on which camera is active

	if (firstCV)
	{
		glTranslatef(camera.getPositionX(), camera.getPositionY(), camera.getPositionZ());
	}

	else if (secondCV)
	{
		glTranslatef(topview.getPositionX(), topview.getPositionY(), topview.getPositionZ());
	}

	else if (thirdCV)
	{
		glTranslatef(overview.getPositionX(), overview.getPositionY(), overview.getPositionZ());
	}

	else if (fourthCV)
	{
		glRotatef(panRotate, 0, 1, 0);
		glTranslatef(panAroundView.getPositionX(), panAroundView.getPositionY(), panAroundView.getPositionZ());
		glRotatef(-panRotate, 0, 1, 0);
		
	}

	
	// skybox object - hand drawn using six quad faces

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

		glBegin(GL_QUADS);

			// front
			glTexCoord2f(0.25, 0.3334);
			glVertex3f(-2, 2, -2);
			glTexCoord2f(0.25, 0.6667);
			glVertex3f(-2, -2, -2);
			glTexCoord2f(0.5, 0.6667);
			glVertex3f(2, -2, -2);
			glTexCoord2f(0.5, 0.3334);
			glVertex3f(2, 2, -2);

		glEnd();

		glBegin(GL_QUADS);

			// top
			glTexCoord2f(0.25, 0);
			glVertex3f(-2, 2, 2);
			glTexCoord2f(0.25, 0.3334);
			glVertex3f(-2, 2, -2);
			glTexCoord2f(0.5, 0.3334);
			glVertex3f(2, 2, -2);
			glTexCoord2f(0.5, 0);
			glVertex3f(2, 2, 2);

		glEnd();

		glBegin(GL_QUADS);

			// left
			glTexCoord2f(0, 0.3334);
			glVertex3f(-2, 2, 2);
			glTexCoord2f(0, 0.6667);
			glVertex3f(-2, -2, 2);
			glTexCoord2f(0.25, 0.6667);
			glVertex3f(-2, -2, -2);
			glTexCoord2f(0.25, 0.3334);
			glVertex3f(-2, 2, -2);

		glEnd();

		glBegin(GL_QUADS);

			// right
			glTexCoord2f(0.5, 0.3334);
			glVertex3f(2, 2, -2);
			glTexCoord2f(0.5, 0.6667);
			glVertex3f(2, -2, -2);
			glTexCoord2f(0.75, 0.6667);
			glVertex3f(2, -2, 2);
			glTexCoord2f(0.75, 0.3334);
			glVertex3f(2, 2, 2);

		glEnd();


		glBegin(GL_QUADS);

			// bottom
			glTexCoord2f(0.25, 0.6667);
			glVertex3f(-2, -2, -2);
			glTexCoord2f(0.25, 1.0);
			glVertex3f(-2, -2, 2);
			glTexCoord2f(0.5, 1.0);
			glVertex3f(2, -2, 2);
			glTexCoord2f(0.5, 0.6667);
			glVertex3f(2, -2, -2);

		glEnd();

		glBegin(GL_QUADS);

			// back
			glTexCoord2f(0.75, 0.3334);
			glVertex3f(2, 2, 2);
			glTexCoord2f(0.75, 0.6667);
			glVertex3f(2, -2, 2);
			glTexCoord2f(1, 0.6667);
			glVertex3f(-2, -2, 2);
			glTexCoord2f(1, 0.3334);
			glVertex3f(-2, 2, 2);

		glEnd();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glBindTexture(GL_TEXTURE_2D, NULL);

	glPopMatrix();
}

