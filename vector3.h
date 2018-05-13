#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <math.h>

typedef struct vec3
{
	float x;
	float y;
	float z;
}vec3;

void vec3_add(vec3* vr, vec3 a, vec3 b);
void vec3_sub(vec3* vr, vec3 a, vec3 b);
void vec3_multiplyScalar(vec3* vr, vec3 a, float s);
void vec3_zeroY(vec3* vr, vec3 a);
void normalize(vec3* v);
float dot(vec3 a, vec3 b);
void cross(vec3* vr, vec3 a, vec3 b);

#endif // VECTOR3_H_