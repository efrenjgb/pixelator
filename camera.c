#include "camera.h"

#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

void camera_init(camera* c, vec3 p, vec3 t, float fov, float znear, float zfar, float speed)
{
	vec3 f = {0.0f, 0.0f, -1.0f};
	vec3 up = {0.0f, 1.0f, 0.0f};
	c->fov = fov;
	c->znear = znear;
	c->zfar = zfar;
	c->position = p;
	c->target = t;
	c->front = f;
	c->up = up;
	c->speed = speed;
	c->yaw = 270.0f;
	c->pitch = 0.0f;
}

void camera_doMovement(camera* c, input in)
{

	if(in.mouseMoved)
	{
		float xoffset = in.cursor.xoffset; 
		float yoffset = in.cursor.yoffset;
		
		float sensitivity = 0.5f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		c->yaw   += xoffset;
		c->pitch += yoffset;

		if(c->pitch > 89.0f)
		    c->pitch = 89.0f;
		if(c->pitch < -89.0f)
		    c->pitch = -89.0f;

		c->front.x = cos(degreesToRadians(c->yaw)) * cos(degreesToRadians(c->pitch));
		c->front.y = sin(degreesToRadians(c->pitch));
		c->front.z = sin(degreesToRadians(c->yaw)) * cos(degreesToRadians(c->pitch));
		normalize(&c->front);
	}

	vec3 frontNoY = c->front;
	//vec3_zeroY(&frontNoY, c->front);

	vec3 camFrontStep;
	vec3_multiplyScalar(&c->step, frontNoY, c->speed);

	vec3 lat;
	cross(&lat, frontNoY, c->up);
	normalize(&lat);
	vec3_multiplyScalar(&lat, lat, c->speed);

	if(in.keys.w){
		vec3_add(&c->position, c->position, c->step);
		//printf("%s\n", "pressing w");
	}
	if(in.keys.s){
		vec3_sub(&c->position, c->position, c->step);
		//printf("%s\n", "pressing s");
	}
	if(in.keys.a){
		vec3_add(&c->position, c->position, lat);
		//printf("%s\n", "pressing a");
	}
	if(in.keys.d){
		vec3_sub(&c->position, c->position, lat);
		//printf("%s\n", "pressing d");
	}

	vec3_add(&c->target, c->position, c->front);
}