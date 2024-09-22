#include "Camera.h"
#include <iostream>

Camera::Camera() {
	printf("Camera created without parameters\n");
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	if (EnableMovementKeys) {
		if (keys[GLFW_KEY_W]) position += front * velocity;

		if (keys[GLFW_KEY_S]) position -= front * velocity;

		if (keys[GLFW_KEY_A]) position -= right * velocity;

		if (keys[GLFW_KEY_D]) position += right * velocity;

		if (keys[GLFW_KEY_Q]) position -= up * velocity;

		if (keys[GLFW_KEY_E]) position += up * velocity;
	}
}

void Camera::scrollControl(GLfloat yChange, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;
	if (EnableMovementKeys) moveSpeed += yChange/20.0f * deltaTime;
	if (moveSpeed < 0.0f) moveSpeed = 0.00001f;
	if (moveSpeed > 50.0f) moveSpeed = 50.f;
	// position += front * yChange * velocity * 0.001f;
}

void Camera::mouseButtons(int* buttons)
{
	EnableMovementKeys = buttons[GLFW_MOUSE_BUTTON_RIGHT] == 1;
	scrollableWindow = buttons[GLFW_MOUSE_BUTTON_LEFT] == 1;
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	float deltaTime = 0.001f;
	GLfloat velocity = moveSpeed * deltaTime;
	if (scrollableWindow) {
		position += front * pitch * velocity;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	} 
	else if (EnableMovementKeys){
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(front);
	}

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
