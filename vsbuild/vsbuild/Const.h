#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <random>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

using namespace std;
using namespace glm;

static GLfloat boxHeight = 6.0f;
static GLfloat boxWidth = 2.0f;
static GLfloat harryWidth = 0.25f;
static GLfloat harryHeight = 1.75f;

// 显示屏幕默认长宽值
// --------------------------------
const GLuint SCR_WIDTH = 1024;
const GLuint SCR_HEIGHT = 500;
const GLuint SHADOW_WIDTH = 1024;
const GLuint SHADOW_HEIGHT = 1024;

//视角模式
// -------
#define FPV 1 // 第一人称视角
#define GPV 2 // 上帝视角

// 显示图片选择
// ------------
#define PIC1 0
#define PIC2 1

#define BUILDING_1
#define SKYSCRAPER
#define VEHICLE
/*
spaceCraft 0.3 1
mechWalker 0.3 1

buildings:
01 0.00005 35: 0 0 0 0 0 0 0
               0 0 0 0 0 0 0
			   0 0 0 * 0 0 0
			   0 0 0 0 0 0 0
			   0 0 0 0 0 0 0

02 0.00005 20: 0 0 0 0
               0 0 0 0
			   0 # 0 0
			   0 0 0 0
			   0 0 0 0

03 

skyScraper
effiel tower 
*/
// 玩家初始化视角
// --------------
//const GLfloat initX = 33.0f;
//const GLfloat initY = -1.0f;
//const GLfloat initZ = 33.0f;

const GLfloat initX = 0.0f;
const GLfloat initY = 0.0f;
const GLfloat initZ = 20.0f;

// 照相机的缺省参数
// ----------------
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM = 45.0f;

// 地图文件的编码
// --------------
#define LAND
#define WATER

// 速度模式
// ----------------------------
const GLfloat ACC_VELOCITY = 5.0f;
const GLfloat DEFAULT_VELOCITY = 3.0f;

// 极小量
// --------------------
const GLfloat eps = 0.0f;

//const char * logl_root = "F:/desk/OPENGL/cg_project";

struct Particle {
	vector<vec3> pos;
	vector<vec3> speed;
	vector<vec3> color;
	GLuint lifespan;
};

struct Magic {
	vector<vec3> pos;
	vec3 speed;
	vec3 color;
	GLuint lifespan;
	GLboolean disappear;
};

// 墙壁立方体坐标向量
// ---------------------------
static GLfloat boxVertices[] = {
// - positions ---------- normals ------------ texture coords ----- //
// ---------------------------------------------------------------- //
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 
	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	  0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	  0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	 -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 
	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	  0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	 -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

// 天空盒坐标向量
// ------------------------------
static GLfloat skyBoxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
};

// 地板坐标向量
// -----------------------------
static GLfloat planeVertices[] = {
// - positions -------------- normals ---------- texcoords ---- //
// ------------------------------------------------------------ //
	 200.0f, -1.0f,  200.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
	-200.0f, -1.0f,  200.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
	-200.0f, -1.0f, -200.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

	 200.0f, -1.0f,  200.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
	-200.0f, -1.0f, -200.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
	 200.0f, -1.0f, -200.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
};