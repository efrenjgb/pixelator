#ifndef BSP_H_
#define BSP_H_

#include <stdlib.h>
#include <string.h>
#include "vector3.h"

#define CP_FRONT 1
#define CP_BACK 2
#define CP_ONPLANE 3
#define CP_SPANNING 4
#define ZeroMemory(p, sz) memset( (p) , 0 , (sz) )


typedef struct polygon
{
	vec3 vertices[10];
	vec3 normal;
	int vertexCount;
	int indicesCount;
	int indices[30];
	struct polygon* next;
}polygon;

typedef struct bspNode{
	struct polygon * splitter;
	struct bspNode * front;
	struct bspNode * back;
	int isLeaf;
	int isSolid;
}bspNode;

polygon* polygon_add(polygon* parent, vec3 *vertices, int nov);
polygon* selectBestSplitter(polygon *PolyList);
void BuildBspTree(bspNode* CurrentNode, polygon* PolyList);
int ClassifyPoint(vec3 pos, polygon* plane);
bspNode* initBsp(void);

#endif // BSP_H_