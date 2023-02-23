#include "RatchetMove.h"

// ratchet constructor setting initial values

RatchetMove::RatchetMove()
{
	// set initial values of rotation for each axis

	Pitch = 0;
	Yaw = 0;
	Roll = 0;

	// set speed values for movement and rotation

	speed = 40;
	rotateSpeed = 100;

	// pi value and 180 value stored for calculating rotation values

	pi = 3.1415f;
	oneEighty = 180;
}

// update function updating position and rotation values every frame

void RatchetMove::Update(float dt)
{
	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;
	// Roll, Pitch and Yall are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(Yaw * pi / oneEighty);
	cosP = cosf(Pitch * pi / oneEighty);
	cosR = cosf(Roll * pi / oneEighty);
	sinY = sinf(Yaw * pi / oneEighty);
	sinP = sinf(Pitch * pi / oneEighty);
	sinR = sinf(Roll * pi / oneEighty);

	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector


	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.

	lookAt = position.operator+(forward);

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this, don’t do it. 

	right = forward.cross(up);
}

// setting movement functions with correct values

void RatchetMove::moveForward(float dt)
{
	position.add(forward, speed * dt);
}

void RatchetMove::moveBackwards(float dt)
{
	position.subtract(forward, speed * dt);
}

void RatchetMove::moveUp(float dt)
{
	position.add(up, speed * dt);

}

void RatchetMove::moveDown(float dt)
{
	position.subtract(up, speed * dt);

}

// setting rotation functions with correct values

void RatchetMove::rotateLeft(float dt)
{
	Yaw--* rotateSpeed* dt;

}

void RatchetMove::rotateRight(float dt)
{
	Yaw++* rotateSpeed* dt;
}

// setting values for position getters
// on each axis

float RatchetMove::getPositionX()
{
	return position.x;
}

float RatchetMove::getPositionY()
{
	return position.y;
}

float RatchetMove::getPositionZ()
{
	return -position.z;
}

// returning the yaw value back to the scene
// allows the ratchet model to rotate

float RatchetMove::getYaw()
{
	return Yaw;
}