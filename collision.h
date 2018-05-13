#ifndef COLLISION_H_
#define COLLISION_H_

#include "vector3.h"

typedef struct circle{
	float x;
	float z;
	float r;
}circle;

typedef struct aabb{
	vec3 min;
	vec3 max;
}aabb;

int aabbvaabb(aabb b1, aabb b2)
{
	return(	b1.max.x > b2.min.x &&
			b1.min.x < b2.max.x &&
			b1.max.y > b2.min.y &&
			b1.min.y < b2.max.y &&
			b1.max.z > b2.min.z &&
			b1.min.z < b2.max.z);
}

#endif