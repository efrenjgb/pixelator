#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <math.h>
#include "vector3.h"

typedef struct mat4
{
	float m[16];
}mat4;

void mat4_lookAtLH(mat4* lam, vec3 eye, vec3 target, vec3 up);
void mat4_projectionFov(mat4 *m, float fov, float width, float height, float z_near, float z_far);
void mat4_identity(mat4* m);
void mat4_translation(mat4* m, vec3 v);
void mat4_multiply(mat4* result, mat4 m1, mat4 m2);
void mat4_print(mat4 m, int id);

#endif // MATRIX_H_