#include "Camera.h"

GLvoid Camera::processKeyBoard(cameraMovement direction, GLfloat deltaT, GLuint viewType)
{
	GLfloat velocity = movementSpeed * deltaT;
	vec3 front2D = normalize(vec3(front.x, 0.0f, front.z));
	vec3 right2D = normalize(vec3(right.x, 0.0f, right.z));
	if (direction == FORWARD)
	{
		if (viewType == FPV)
		{
			position += front2D * velocity;
			if (position.y < -1.0f) position.y = -1.0f;
		}
		else if (viewType == GPV)
		{
			position += front * velocity;
			if (position.y < 0.0f) position.y = 0.0f;
		}
	}
	else if (direction == BACKWARD)
	{
		if (viewType == FPV || viewType == GPV)
		{
			position -= front2D * velocity;
			if (position.y < -1.0f) position.y = -1.0f;
		}
		else if (viewType == GPV)
		{
			position -= front * velocity;
			if (position.y < 0.0f) position.y = 0.0f;
		}
	}
	else if (direction == LEFT)
	{
		if (viewType == FPV)
		{
			position -= right2D * velocity;
			if (position.y < -1.0f) position.y = -1.0f;
		}
		else if (viewType == GPV)
		{
			position -= right * velocity;
			if (position.y < 0.0f) position.y = 0.0f;
		}
	}
	else if (direction == RIGHT)
	{
		if (viewType == FPV)
		{
			position += right2D * velocity;
			if (position.y < -1.0f) position.y = -1.0f;
		}
		else if (viewType == GPV)
		{
			position += right * velocity;
			if (position.y < 0.0f) position.y = 0.0f;
		}
	}
}

// zoom-in zoom-out ¹¦ÄÜÄ£¿é
// -------------------------
GLvoid Camera::processMouseScroll(GLfloat y)
{
	zoom -= y;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}

GLvoid Camera::updateCameraVectors()
{
	vec3 tmp;
	tmp.x = cos(radians(yaw)) * cos(radians(pitch));
	tmp.y = sin(radians(pitch));
	tmp.z = sin(radians(yaw)) * cos(radians(pitch));
	front = normalize(tmp);

	right = normalize(cross(front, upVec));
	up = normalize(cross(right, front));
}