#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"

class Camera
{
public:

	// declare camera constructor
	Camera::Camera();

	// updates camera when called in scene

	void Camera::Update(float dt);
	

	// getters and setters for the position of the camera
	// and the look at position for the camera 

	GLdouble Camera::getPositionX();

	void Camera::setPositionX(float x);

	GLdouble  Camera::getPositionY();

	void Camera::setPositionY(float y);

	GLdouble Camera::getPositionZ();

	void Camera::setPositionZ(float z);

	GLdouble Camera::getLookAtX();

	GLdouble Camera::getLookAtY();

	GLdouble Camera::getLookAtZ();

	void Camera::setLookAtX(float x);

	void Camera::setLookAtY(float y);

	void Camera::setLookAtZ(float z);

	// getters for the getUp variable within the camera

	GLdouble Camera::getUpX();

	GLdouble Camera::getUpY();

	GLdouble Camera::getUpZ();

	// movement functions  camera
	// forwards - backwards - left - right - up - down

	void Camera::moveForward(float dt);
	void Camera::moveBackwards(float dt);
	void Camera::moveUp(float dt);
	void Camera::moveDown(float dt);
	void Camera::moveLeft(float dt);
	void Camera::moveRight(float dt);

	// rotate functions for the camera
	// up - down - left - right
	// implemented the rotateLeft and rotateRight functions
	// within the RatchetMove class

	void Camera::rotateUp(float dt);
	void Camera::rotateDown(float dt);
	void Camera::rotateLeft(float dt);
	void Camera::rotateRight(float dt);

	// rotate functions for the camera
	// using the mouse for the aiming instead

	void Camera::changeYaw(float y);
	void Camera::changePitch(float p);

protected:

	// variables
	// Vector3 variables calculating the overall movement
	// float variables to determine camera speed 
	// and angle / rotation

	Vector3 position, lookAt, forward, up, right;
	float Pitch, Yaw, Roll;
	float speed, rotateSpeed;
	float pi, oneEighty;
};

