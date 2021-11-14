#pragma once

#include "Const.h"
#include "Camera.h"
#include "CollisionDetection.h"
#include "Particle.h"

extern GLboolean firstMouse, isMagic, isNight, isgamma, ishdr, isShadow, dirlight;
extern GLfloat lastX, lastY, deltaTime, lastFrame;
extern Camera camera;
extern Magic ma;
extern GLuint viewType, state;

GLvoid framebuffer_size_callback(GLFWwindow * window, int width, int height);
GLvoid mouse_callback(GLFWwindow * window, double xpos, double ypos);
GLvoid mouse_button_callback(GLFWwindow * window, int button, int action, int mod);
GLvoid scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
GLvoid processInput(GLFWwindow * window, Camera & player, Camera & camera);