#pragma once
#include "Const.h"

class Element {
public:
	vec3 position;
	vec3 volume;
	vec3 front;
	GLboolean isDead = false;
	GLfloat zoomRate = 1.0f;
	GLfloat rotateAngle = 0.0f;
	GLuint type;
	Element();
	Element(GLuint type, GLfloat zoom_rate, vec3 volume, vec3 position);
	~Element();
	GLvoid updateAngle(vec3 targetPosition);
private:
	GLvoid dead();
};
