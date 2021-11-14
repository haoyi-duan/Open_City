#pragma once
#include "Const.h"
#include "Shader.h"

extern GLuint planeVAO, quadVAO, quadVBO, cVAO, cVBO, screenVAO, screenVBO;
extern vector<vec3> boxPosition;

GLvoid renderScene(const Shader & shader);
GLvoid renderScreen();
GLvoid renderQuad();
GLvoid renderCube();