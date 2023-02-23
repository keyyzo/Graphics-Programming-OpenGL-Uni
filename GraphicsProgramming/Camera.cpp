#include "Camera.h"

// camera constructor setting initial values

Camera::Camera()
{
	// set initial position of camera within the scene

	position.setX(-5);
	position.setY(10);
	position.setZ(55);

	// set initial values of rotation for each axis

	Pitch = 0;
	Yaw = 0;
	Roll = 0;

	// set speed values for movement and rotation

	speed = 20;
	rotateSpeed = 1.5;

	// pi value and 180 value stored for calculating rotation values

	pi = 3.1415f;
	oneEighty = 180;
}

// update function updating position and rotation values every frame
void Camera::Update(float dt)
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

// setting values for position getters and setters
// on each axis

GLdouble Camera::getPositionX()
{
	return position.x;
}

void Camera::setPositionX(float x)
{
	position.x = x;
}

GLdouble Camera::getPositionY()
{
	return position.y;
}

void Camera::setPositionY(float y)
{
	position.y = y;
}
GLdouble Camera::getPositionZ()
{
	return position.z;
}

void Camera::setPositionZ(float z)
{
	position.z = z;
}

// setting values for lookAt getters and setters
// on each axis

GLdouble Camera::getLookAtX()
{
	return lookAt.x;
}

GLdouble Camera::getLookAtY()
{
	return lookAt.y;
}

GLdouble Camera::getLookAtZ()
{
	return lookAt.z;
}

void Camera::setLookAtX(float x)
{
	lookAt.x = x;
}

void Camera::setLookAtY(float y)
{
	lookAt.y = y;
}

void Camera::setLookAtZ(float z)
{
	lookAt.z = z;
}

// setting getters for getUp on each axis

GLdouble Camera::getUpX()
{
	return up.x;
}

GLdouble Camera::getUpY()
{
	return up.y;
}
GLdouble Camera::getUpZ()
{
	return up.z;
}

// setting movement functions with correct values

void Camera::moveForward(float dt)
{
	position.add(forward,speed*dt);
}

void Camera::moveBackwards(float dt)
{
	position.subtract(forward, speed * dt);
}

void Camera::moveUp(float dt)
{
	position.add(up, speed * dt);
	
}

void Camera::moveDown(float dt)
{
	position.subtract(up, speed * dt);

}

void Camera::moveLeft(float dt)
{
	position.subtract(right, speed * dt);
}

void Camera::moveRight(float dt)
{
	position.add(right, speed * dt);
}

// setting rotation functions with correct values

void Camera::rotateUp(float dt)
{
	Pitch++ * rotateSpeed * dt;
}
void Camera::rotateDown(float dt)
{
	Pitch-- * rotateSpeed * dt;
}
void Camera::rotateLeft(float dt)
{
	Yaw-- * rotateSpeed * dt;
	
}
void Camera::rotateRight(float dt)
{
	Yaw++ * rotateSpeed * dt;
}

// setting rotation functions with correct values
// for mouse control
// multiplied by 0.05 to smooth
// and slow down the mouse control

void Camera::changeYaw(float y)
{
	Yaw += y*0.05;
}
void Camera::changePitch(float p)
{
	Pitch += p*0.05;
}
