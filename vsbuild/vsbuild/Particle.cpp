#include "Particle.h"

struct Magic initMagic(vec3 position, GLuint lifespan, vec3 front, vec3 color, GLfloat eps)
{
	Magic p;
	GLfloat temp = randFloat(-0.001, 0.001);
	p.pos.push_back(position + vec3(eps, eps, randFloat(-0.001, 0.001)));
	p.pos.push_back(position + vec3(-eps, -eps, randFloat(-0.001, 0.001)));
	p.pos.push_back(position + vec3(eps, randFloat(-0.001, 0.001), eps));
	p.pos.push_back(position + vec3(-eps, randFloat(-0.001, 0.001), -eps));
	p.pos.push_back(position + vec3(randFloat(-0.001, 0.001), eps, eps));
	p.pos.push_back(position + vec3(randFloat(-0.001, 0.001), -eps, -eps));
	p.pos.push_back(position + vec3(eps, -eps, randFloat(-0.001, 0.001)));
	p.pos.push_back(position + vec3(-eps, eps, randFloat(-0.001, 0.001)));
	p.pos.push_back(position + vec3(eps, randFloat(-0.001, 0.001), -eps));
	p.pos.push_back(position + vec3(-eps, randFloat(-0.001, 0.001), eps));
	p.pos.push_back(position + vec3(randFloat(-0.001, 0.001), eps, -eps));
	p.pos.push_back(position + vec3(randFloat(-0.001, 0.001), -eps, eps));
	p.speed = normalize(front);
	p.color = color;
	p.lifespan = lifespan;
	p.disappear = false;
	return p;
}

GLvoid updateMagic(vec3 time, Magic &myma)
{
	for (unsigned int i = 0; i < myma.pos.size(); i++)
	{
		if (myma.lifespan == 0 || !collisionDetection(myma.pos[i], 0.01f, 0.01f) || myma.pos[i].y <= -1.0f)
		{
			isMagic = false;
			isParticle = true;
			p = initParticle(myma.pos[0], 3000, 100, vec3(0.8, 0, 0), 0.5);
			break;
		}
		myma.pos[i] = myma.pos[i] + myma.speed * time;
	}
	myma.lifespan--;
}

struct Particle initParticle(vec3 position, GLuint lifespan, GLuint num, vec3 color, GLfloat eps)
{
	GLuint ParticleNumber = num;
	Particle p;
	for (unsigned int i = 0; i < ParticleNumber; i++)
	{
		p.pos.push_back(position);
		p.speed.push_back(vec3(0.00f, 0.0f, 0.00f));
		GLfloat a, b, c;
		a = randFloat(-eps, eps);
		b = randFloat(-eps, eps);
		c = randFloat(-eps, eps);
		vec3 temp = vec3(a, b, c);
		p.color.push_back(temp + color);
		p.lifespan = lifespan;
	}
	return p;
}

GLvoid updateParticle(vec3 time, Particle &p)
{
	for (unsigned int i = 0; i < p.pos.size(); i++)
	{
		if (p.lifespan == 0)
			break;
		p.pos[i] = p.pos[i] + p.speed[i] * time;
		GLfloat a, b, c;
		a = randFloat(-0.0001, 0.0001);
		b = randFloat(-0.0001, 0.0001);
		c = randFloat(-0.0001, 0.0001);
		vec3 temp = vec3(a, b, c);
		p.speed[i] = p.speed[i] + temp;
	}
	p.lifespan--;
}