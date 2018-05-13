#include "matrix.h"

void mat4_lookAtLH(mat4* lam, vec3 eye, vec3 target, vec3 up)
{
	//forward vector
	vec3 zaxis;
	vec3_sub(&zaxis, eye, target);
	normalize(&zaxis);

	//right vector
	vec3 xaxis;
	cross(&xaxis, up, zaxis);
	normalize(&xaxis);

	//up vector
	vec3 yaxis;
	cross(&yaxis, zaxis, xaxis);
	normalize(&yaxis);

	lam->m[0]  = xaxis.x;
	lam->m[1]  = yaxis.x;
	lam->m[2]  = zaxis.x;
	lam->m[3]  = 0;
	lam->m[4]  = xaxis.y;
	lam->m[5]  = yaxis.y;
	lam->m[6]  = zaxis.y;
	lam->m[7]  = 0;
	lam->m[8]  = xaxis.z;
	lam->m[9]  = yaxis.z;
	lam->m[10] = zaxis.z;
	lam->m[11] = 0;
	lam->m[12] = -dot(xaxis, eye);
	lam->m[13] = -dot(yaxis, eye);
	lam->m[14] = -dot(zaxis, eye);
	lam->m[15] = 1.0f;
}

void mat4_projectionFov(mat4 *m, float fov, float width, float height, float z_near, float z_far)
{
    float ar = width / height;
    float tan_half_fov = tan((fov / 2.0f) * ( M_PI / 180.0f));
    float z_range = z_near - z_far;
	m->m[0] = 1.0f / (tan_half_fov * ar);
	m->m[1] = 0;
	m->m[2] = 0;
	m->m[3] = 0;
	m->m[4] = 0;
	m->m[5] = 1.0f / (tan_half_fov);
	m->m[6] = 0;
	m->m[7] = 0;
	m->m[8] = 0;
	m->m[9] = 0;
	m->m[10] = -(z_near + z_far) / z_range;
	m->m[11] = -(2.0f * z_far * z_near / z_range);
	m->m[12] = 0;
	m->m[13] = 0;
	m->m[14] = -1.0f;
	m->m[15] = 0;
}

void mat4_identity(mat4* m)
{
	m->m[0] = 1.0f;
	m->m[1] = 0;
	m->m[2] = 0;
	m->m[3] = 0;

	m->m[4] = 0;
	m->m[5] = 1.0f;
	m->m[6] = 0;
	m->m[7] = 0;

	m->m[8] = 0;
	m->m[9] = 0;
	m->m[10] = 1.0f;
	m->m[11] = 0;

	m->m[12] = 0;
	m->m[13] = 0;
	m->m[14] = 0;
	m->m[15] = 1.0f;
}

void mat4_translation(mat4* m, vec3 v)
{
	m->m[0] = 1.0f;
	m->m[1] = 0;
	m->m[2] = 0;
	m->m[3] = 0;

	m->m[4] = 0;
	m->m[5] = 1.0f;
	m->m[6] = 0;
	m->m[7] = 0;

	m->m[8] = 0;
	m->m[9] = 0;
	m->m[10] = 1.0f;
	m->m[11] = 0;

	m->m[12] = v.x;
	m->m[13] = v.y;
	m->m[14] = v.z;
	m->m[15] = 1.0f;
}

void mat4_multiply(mat4* result, mat4 m1, mat4 m2)
{
	result->m[0] = m1.m[0] * m2.m[0] + m1.m[1] * m2.m[4] + m1.m[2] * m2.m[8] + m1.m[3] * m2.m[12];
	result->m[1] = m1.m[0] * m2.m[1] + m1.m[1] * m2.m[5] + m1.m[2] * m2.m[9] + m1.m[3] * m2.m[13];
	result->m[2] = m1.m[0] * m2.m[2] + m1.m[1] * m2.m[6] + m1.m[2] * m2.m[10] + m1.m[3] * m2.m[14];
	result->m[3] = m1.m[0] * m2.m[3] + m1.m[1] * m2.m[7] + m1.m[2] * m2.m[11] + m1.m[3] * m2.m[15];
	result->m[4] = m1.m[4] * m2.m[0] + m1.m[5] * m2.m[4] + m1.m[6] * m2.m[8] + m1.m[7] * m2.m[12];
	result->m[5] = m1.m[4] * m2.m[1] + m1.m[5] * m2.m[5] + m1.m[6] * m2.m[9] + m1.m[7] * m2.m[13];
	result->m[6] = m1.m[4] * m2.m[2] + m1.m[5] * m2.m[6] + m1.m[6] * m2.m[10] + m1.m[7] * m2.m[14];
	result->m[7] = m1.m[4] * m2.m[3] + m1.m[5] * m2.m[7] + m1.m[6] * m2.m[11] + m1.m[7] * m2.m[15];
	result->m[8] = m1.m[8] * m2.m[0] + m1.m[9] * m2.m[4] + m1.m[10] * m2.m[8] + m1.m[11] * m2.m[12];
	result->m[9] = m1.m[8] * m2.m[1] + m1.m[9] * m2.m[5] + m1.m[10] * m2.m[9] + m1.m[11] * m2.m[13];
	result->m[10] = m1.m[8] * m2.m[2] + m1.m[9] * m2.m[6] + m1.m[10] * m2.m[10] + m1.m[11] * m2.m[14];
	result->m[11] = m1.m[8] * m2.m[3] + m1.m[9] * m2.m[7] + m1.m[10] * m2.m[11] + m1.m[11] * m2.m[15];
	result->m[12] = m1.m[12] * m2.m[0] + m1.m[13] * m2.m[4] + m1.m[14] * m2.m[8] + m1.m[15] * m2.m[12];
	result->m[13] = m1.m[12] * m2.m[1] + m1.m[13] * m2.m[5] + m1.m[14] * m2.m[9] + m1.m[15] * m2.m[13];
	result->m[14] = m1.m[12] * m2.m[2] + m1.m[13] * m2.m[6] + m1.m[14] * m2.m[10] + m1.m[15] * m2.m[14];
	result->m[15] = m1.m[12] * m2.m[3] + m1.m[13] * m2.m[7] + m1.m[14] * m2.m[11] + m1.m[15] * m2.m[15];
}

void mat4_print(mat4 m, int id)
{
	printf("%d\n", id);
	printf("|%f, %f, %f, %f|\n", m.m[0],m.m[1],m.m[2],m.m[3]);
	printf("|%f, %f, %f, %f|\n", m.m[4],m.m[5],m.m[6],m.m[7]);
	printf("|%f, %f, %f, %f|\n", m.m[8],m.m[9],m.m[10],m.m[11]);
	printf("|%f, %f, %f, %f|\n", m.m[12],m.m[13],m.m[14],m.m[15]);
	printf("\n");
}