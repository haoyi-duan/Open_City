#include "CollisionDetection.h"

GLboolean collisionDetection(vec3& position, GLfloat radius)
{
	GLfloat curx = position.x, cury = position.y, curz = position.z;
	GLfloat leftEdge = curx - radius;
	GLfloat rightEdge = curx + radius;
	GLfloat frontEdge = curz - radius;
	GLfloat backEdge = curz + radius;
	for (unsigned int i = 0; i < boxPosition.size(); i++)
	{
		if (leftEdge > boxPosition[i].x - boxWidth / 2 && leftEdge < boxPosition[i].x + boxWidth / 2 && frontEdge > boxPosition[i].z - boxWidth / 2 && frontEdge < boxPosition[i].z + boxWidth / 2)
		{
			GLfloat a = leftEdge - (boxPosition[i].x - boxWidth / 2);
			GLfloat b = (boxPosition[i].x + boxWidth / 2) - leftEdge;
			GLfloat c = frontEdge - (boxPosition[i].z - boxWidth / 2);
			GLfloat d = (boxPosition[i].z + boxWidth / 2) - frontEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = boxPosition[i].x - boxWidth / 2 - eps + radius;
			if (min == b)
				position.x = boxPosition[i].x + boxWidth / 2 + eps + radius;
			if (min == c)
				position.z = boxPosition[i].z - boxWidth / 2 - eps + radius;
			if (min == d)
				position.z = boxPosition[i].z + boxWidth / 2 + eps + radius;
			return false;
		}
		if (leftEdge > boxPosition[i].x - boxWidth / 2 && leftEdge < boxPosition[i].x + boxWidth / 2 && backEdge > boxPosition[i].z - boxWidth / 2 && backEdge < boxPosition[i].z + boxWidth
			/ 2)
		{
			GLfloat a = leftEdge - (boxPosition[i].x - boxWidth / 2);
			GLfloat b = (boxPosition[i].x + boxWidth / 2) - leftEdge;
			GLfloat c = backEdge - (boxPosition[i].z - boxWidth / 2);
			GLfloat d = (boxPosition[i].z + boxWidth / 2) - backEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = boxPosition[i].x - boxWidth / 2 - eps + radius;
			if (min == b)
				position.x = boxPosition[i].x + boxWidth / 2 + eps + radius;
			if (min == c)
				position.z = boxPosition[i].z - boxWidth / 2 - eps - radius;
			if (min == d)
				position.z = boxPosition[i].z + boxWidth / 2 + eps - radius;
			return false;
		}
		if (rightEdge > boxPosition[i].x - boxWidth / 2 && rightEdge < boxPosition[i].x + boxWidth / 2 && backEdge > boxPosition[i].z - boxWidth / 2 && backEdge < boxPosition[i].z + boxWidth / 2)
		{
			GLfloat a = rightEdge - (boxPosition[i].x - boxWidth / 2);
			GLfloat b = (boxPosition[i].x + boxWidth / 2) - rightEdge;
			GLfloat c = backEdge - (boxPosition[i].z - boxWidth / 2);
			GLfloat d = (boxPosition[i].z + boxWidth / 2) - backEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = boxPosition[i].x - boxWidth / 2 - eps - radius;
			if (min == b)
				position.x = boxPosition[i].x + boxWidth / 2 + eps - radius;
			if (min == c)
				position.z = boxPosition[i].z - boxWidth / 2 - eps - radius;
			if (min == d)
				position.z = boxPosition[i].z + boxWidth / 2 + eps - radius;
			return false;
		}
		if (rightEdge > boxPosition[i].x - boxWidth / 2 && rightEdge < boxPosition[i].x + boxWidth / 2 && frontEdge > boxPosition[i].z - boxWidth / 2 && frontEdge < boxPosition[i].z + boxWidth / 2)
		{
			GLfloat a = rightEdge - (boxPosition[i].x - boxWidth / 2);
			GLfloat b = (boxPosition[i].x + boxWidth / 2) - rightEdge;
			GLfloat c = frontEdge - (boxPosition[i].z - boxWidth / 2);
			GLfloat d = (boxPosition[i].z + boxWidth / 2) - frontEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = boxPosition[i].x - boxWidth / 2 - eps - radius;
			if (min == b)
				position.x = boxPosition[i].x + boxWidth / 2 + eps - radius;
			if (min == c)
				position.z = boxPosition[i].z - boxWidth / 2 - eps + radius;
			if (min == d)
				position.z = boxPosition[i].z + boxWidth / 2 + eps + radius;
			return false;
		}
	}

	for (unsigned int i = 0; i < elementCount; i++)
	{
		if (leftEdge > elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& leftEdge < elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& frontEdge > elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate
			&& frontEdge < elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate)
		{
			GLfloat a = leftEdge - (elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate);
			GLfloat b = (elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate) - leftEdge;
			GLfloat c = frontEdge - (elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate);
			GLfloat d = (elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate) - frontEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate - eps + radius;
			if (min == b)
				position.x = elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate + eps + radius;
			if (min == c)
				position.z = elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate - eps + radius;
			if (min == d)
				position.z = elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate + eps + radius;
			return false;
		}
		if (leftEdge > elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& leftEdge < elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& backEdge > elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate
			&& backEdge < elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate)
		{
			GLfloat a = leftEdge - (elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate);
			GLfloat b = (elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate) - leftEdge;
			GLfloat c = backEdge - (elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate);
			GLfloat d = (elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate) - backEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate - eps + radius;
			if (min == b)
				position.x = elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate + eps + radius;
			if (min == c)
				position.z = elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate - eps - radius;
			if (min == d)
				position.z = elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate + eps - radius;
			return false;
		}
		if (rightEdge > elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& rightEdge < elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& backEdge > elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate
			&& backEdge < elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate)
		{
			GLfloat a = rightEdge - (elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate);
			GLfloat b = (elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate) - rightEdge;
			GLfloat c = backEdge - (elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate);
			GLfloat d = (elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate) - backEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate - eps - radius;
			if (min == b)
				position.x = elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate + eps - radius;
			if (min == c)
				position.z = elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate - eps - radius;
			if (min == d)
				position.z = elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate + eps - radius;
			return false;
		}
		if (rightEdge > elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& rightEdge < elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate
			&& frontEdge > elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate
			&& frontEdge < elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate)
		{
			GLfloat a = rightEdge - (elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate);
			GLfloat b = (elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate) - rightEdge;
			GLfloat c = frontEdge - (elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate);
			GLfloat d = (elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate) - frontEdge;
			GLfloat min = (a < b) ? (a < c ? a : c) : (b < c ? b : c);
			min = (min < d) ? min : d;
			if (min == a)
				position.x = elementVector[i]->position.x - elementVector[i]->volume.x *  elementVector[i]->zoomRate - eps - radius;
			if (min == b)
				position.x = elementVector[i]->position.x + elementVector[i]->volume.x *  elementVector[i]->zoomRate + eps - radius;
			if (min == c)
				position.z = elementVector[i]->position.z - elementVector[i]->volume.z *  elementVector[i]->zoomRate - eps + radius;
			if (min == d)
				position.z = elementVector[i]->position.z + elementVector[i]->volume.z *  elementVector[i]->zoomRate + eps + radius;
			return false;
		}
	}
	return true;
}

GLboolean collisionDetection(vec3 & position, GLfloat width, GLfloat height)
{
	GLfloat curx = position.x, cury = position.y, curz = position.z;
	GLfloat leftEdge = curx - width / 2;
	GLfloat rightEdge = curx + width / 2;
	GLfloat frontEdge = curz - width / 2;
	GLfloat backEdge = curz + width / 2;
	GLfloat bottomEdge = cury - height / 2;
	GLfloat topEdge = cury + height / 2;
	for (unsigned int i = 0; i < boxPosition.size(); i++)
	{
		if (leftEdge > boxPosition[i].x - boxWidth / 2 && leftEdge < boxPosition[i].x + boxWidth / 2
			&& frontEdge > boxPosition[i].z - boxWidth / 2 && frontEdge < boxPosition[i].z + boxWidth / 2
			&& topEdge > boxPosition[i].y - boxHeight / 2 && topEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}

		if (leftEdge > boxPosition[i].x - boxWidth / 2 && leftEdge < boxPosition[i].x + boxWidth / 2
			&& frontEdge > boxPosition[i].z - boxWidth / 2 && frontEdge < boxPosition[i].z + boxWidth / 2
			&& bottomEdge > boxPosition[i].y - boxHeight / 2 && bottomEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}

		if (leftEdge > boxPosition[i].x - boxWidth / 2 && leftEdge < boxPosition[i].x + boxWidth / 2
			&& backEdge > boxPosition[i].z - boxWidth / 2 && backEdge < boxPosition[i].z + boxWidth / 2
			&& topEdge > boxPosition[i].y - boxHeight / 2 && topEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}

		if (leftEdge > boxPosition[i].x - boxWidth / 2 && leftEdge < boxPosition[i].x + boxWidth / 2
			&& backEdge > boxPosition[i].z - boxWidth / 2 && backEdge < boxPosition[i].z + boxWidth / 2
			&& bottomEdge > boxPosition[i].y - boxHeight / 2 && bottomEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}

		if (rightEdge > boxPosition[i].x - boxWidth / 2 && rightEdge < boxPosition[i].x + boxWidth / 2
			&& backEdge > boxPosition[i].z - boxWidth / 2 && backEdge < boxPosition[i].z + boxWidth / 2
			&& topEdge > boxPosition[i].y - boxHeight / 2 && topEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}

		if (rightEdge > boxPosition[i].x - boxWidth / 2 && rightEdge < boxPosition[i].x + boxWidth / 2
			&& backEdge > boxPosition[i].z - boxWidth / 2 && backEdge < boxPosition[i].z + boxWidth / 2
			&& bottomEdge > boxPosition[i].y - boxHeight / 2 && bottomEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}

		if (rightEdge > boxPosition[i].x - boxWidth / 2 && rightEdge < boxPosition[i].x + boxWidth / 2
			&& frontEdge > boxPosition[i].z - boxWidth / 2 && frontEdge < boxPosition[i].z + boxWidth / 2
			&& topEdge > boxPosition[i].y - boxHeight / 2 && topEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}

		if (rightEdge > boxPosition[i].x - boxWidth / 2 && rightEdge < boxPosition[i].x + boxWidth / 2
			&& frontEdge > boxPosition[i].z - boxWidth / 2 && frontEdge < boxPosition[i].z + boxWidth / 2
			&& bottomEdge > boxPosition[i].y - boxHeight / 2 && bottomEdge < boxPosition[i].y + boxHeight / 2)
		{
			return false;
		}
	}
	return true;
}