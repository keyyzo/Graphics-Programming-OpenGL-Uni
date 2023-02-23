#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include "Model.h"

// inherited the model class
// as this class will be a controllable object
// so being able to pass in render functions
// made creating the object easier

class RatchetMove  : public Model
{
public:

	// declare Ratchet constructor

	RatchetMove::RatchetMove();

	// updates ratchet every frame when called in scene

	void RatchetMove::Update(float dt);

	// getters for the position of ratchet

	float RatchetMove::getPositionX();
	float RatchetMove::getPositionY();
	float RatchetMove::getPositionZ();

	// movement functions for ratchet
	// forwards - backwards - up - down

	void RatchetMove::moveForward(float dt);
	void RatchetMove::moveBackwards(float dt);
	void RatchetMove::moveUp(float dt);
	void RatchetMove::moveDown(float dt);

	// rotate functions for ratchet
	// right - left

	void RatchetMove::rotateLeft(float dt);
	void RatchetMove::rotateRight(float dt);

	// getYaw function to help rotate model 
	// when scene is running

	float RatchetMove::getYaw();

protected:

	// variables
	// Vector3 variables calculating the overall movement
	// float variables to determine movement speed 
	// and angle / rotation

	Vector3 position, lookAt, forward, up, right;
	float Pitch, Yaw, Roll;
	float speed, rotateSpeed;
	float pi, oneEighty;

};

