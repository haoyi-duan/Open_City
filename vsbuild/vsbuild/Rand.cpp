#include "Rand.h"
#include "Const.h"

GLfloat randFloat(GLfloat a, GLfloat b) {
	return a + (b - a)*(1.0*rand() / RAND_MAX);
}

GLuint randInt(GLuint a, GLuint b) {
	return a + rand() % (b - a);
}