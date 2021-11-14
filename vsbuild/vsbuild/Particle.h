#pragma once
#include "Const.h"
#include "Rand.h"
#include "CollisionDetection.h"

extern GLboolean isMagic, isParticle;
extern Particle p;

struct Magic initMagic(vec3 position, GLuint lifespan, vec3 front, vec3 color, GLfloat eps);
GLvoid updateMagic(vec3 time, Magic & p);
struct Particle initParticle(vec3 position, GLuint lifespan, GLuint num, vec3 color, GLfloat eps);
GLvoid updateParticle(vec3 time, Particle & p);