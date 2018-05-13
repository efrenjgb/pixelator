#ifndef MESH_H_
#define MESH_H_

#include <jansson.h>
#include "vector3.h"

typedef struct face
{
	int a;
	int b;
	int c;
} face;

typedef struct mesh
{
	vec3* vertices;
	face* faces;
	vec3 position;
	vec3 rotation;
	int vertexCount;
	int faceCount;
}mesh;

void mesh_init(mesh* m, char* filename);
void mesh_map_init(char* filename);
void mesh_free(mesh* m);

#endif