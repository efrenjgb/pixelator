#include "vector3.h"

void vec3_add(vec3* vr, vec3 a, vec3 b)
{
	vr->x = a.x + b.x;
	vr->y = a.y + b.y;
	vr->z = a.z + b.z;
}

void vec3_sub(vec3* vr, vec3 a, vec3 b)
{
	vr->x = a.x - b.x;
	vr->y = a.y - b.y;
	vr->z = a.z - b.z;
}

void vec3_multiplyScalar(vec3* vr, vec3 a, float s)
{
	vr->x = a.x * s;
	vr->y = a.y * s;
	vr->z = a.z * s;
}

void vec3_zeroY(vec3* vr, vec3 a)
{
	vr->x = a.x;
	vr->y = 0.0f;
	vr->z = a.z;
}

void normalize(vec3* v)
{
	float lenSquared = (v->x * v->x) + (v->y * v->y) + (v->z * v->z);
	float len = sqrt(lenSquared);

	v->x = v->x / len;
	v->y = v->y / len;
	v->z = v->z / len;
}

float dot(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

void cross(vec3* vr, vec3 a, vec3 b)
{
	vr->x = (a.y * b.z) - (a.z * b.y);
	vr->y = (a.z * b.x) - (a.x * b.z);
	vr->z = (a.x * b.y) - (a.y * b.x);
}