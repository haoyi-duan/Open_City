#pragma once

#include "Const.h"
#include "Element.h"

extern vector<vec3> boxPosition;
extern vec3 cupPosition;
extern Element * elementVector[100];
extern GLuint elementCount;

GLvoid createMap(const string filename);
GLuint loadCubemap(vector<string> faces);