#pragma once
#include "Const.h"
#include "Element.h"

extern vector<vec3> boxPosition;
extern GLuint elementCount;
extern Element * elementVector[100];

GLboolean collisionDetection(vec3& position, GLfloat width, GLfloat height);
GLboolean collisionDetection(vec3& position, GLfloat radius);