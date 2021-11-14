#include "Element.h"
#define PI 3.1415926

Element::Element()
{
	this->type = 1;
	this->zoomRate = 1.0f;
	this->volume = { 1.0f, 1.0f, 1.0f };
	this->position = { -1.0f, -1.0f, -1.0f };
}

Element::Element(GLuint type, GLfloat zoomRate, vec3 volume, vec3 position)
{
	this->type = type;
	this->zoomRate = zoomRate;
	this->volume = volume;
	this->position = position;
}

Element::~Element() {}

void Element::updateAngle(vec3 targetPosition)
{
	vec3 frontin3D = (targetPosition - this->position);
	this->front = normalize(frontin3D);
	vec2 frontin2D = normalize(vec2(frontin3D.x, frontin3D.z));
	if (frontin2D.x >= 0)
		this->rotateAngle = acos(frontin2D.y);
	else
		this->rotateAngle = -acos(frontin2D.y);
}

void Element::dead()
{
	this->zoomRate = 0.0f;
}