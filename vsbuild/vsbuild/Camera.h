#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Const.h"

enum cameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class Camera
{
public:
	// 照相机相关属性
	// ------------------------------------
	vec3 position, front, up, right, upVec;
	
	// 欧拉角
	// ----------------
	GLfloat yaw, pitch;
	
	// 照相机参数选项
	// -------------------------------------------
	GLfloat movementSpeed, mouseSensitivity, zoom;

	// 构造函数
	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH) : front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		this->position = position;
		upVec = up;
		this->yaw = yaw;
		this->pitch = pitch;
		updateCameraVectors();
	}
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : front(vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		position = vec3(posX, posY, posZ);
		upVec = vec3(upX, upY, upZ);
		this->yaw = yaw;
		this->pitch = pitch;
		updateCameraVectors();
	}
	
	mat4 getViewMatrix()
	{
		return lookAt(position, position + front, up);
	}

	GLvoid processKeyBoard(cameraMovement direction, GLfloat deltaT, GLuint viewType);


	// 根据鼠标移动情况进行欧拉角的变换
	// --------------------------------
	GLvoid processMouseMovement(GLfloat x, GLfloat y, GLboolean constrainPitch = true)
	{
		x *= mouseSensitivity;
		y *= mouseSensitivity;

		yaw += x;
		pitch += y;

		// 保证仰角不会偏大或者偏小
		// ------------------------
		if (constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.f;
			else if (pitch < -89.f)
				pitch = -89.0f;
		}
		updateCameraVectors();
	}

	// zoom-in zoom-out 功能模块
	// -------------------------
	GLvoid processMouseScroll(GLfloat y);

private:
	GLvoid updateCameraVectors();
};

#endif // !_CAMERA_H_

