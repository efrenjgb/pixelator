#ifndef CAMERA_H_
#define CAMERA_H_

#include "vector3.h"
#include "input.h"

typedef struct camera
{
	float fov;
	float znear;
	float zfar;
	vec3 position;
	vec3 target;
	vec3 front;
	vec3 up;
	vec3 step;
	float speed;
	float yaw;
	float pitch;
}camera;

void camera_init(camera* c, vec3 p, vec3 t, float fov, float znear, float zfar, float speed);
void camera_doMovement(camera* c, input in);

#endif // CAMERA_H_