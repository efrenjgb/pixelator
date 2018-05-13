#include <stdio.h>
#include "bsp.h"

void polygon_print(polygon* iter)
{
	printf("%f,%f,%f\n", iter->vertices[0].x, iter->vertices[0].y, iter->vertices[0].z);
	printf("%f,%f,%f\n", iter->vertices[1].x, iter->vertices[1].y, iter->vertices[1].z);
	printf("%f,%f,%f\n", iter->vertices[2].x, iter->vertices[2].y, iter->vertices[2].z);
	printf("%f,%f,%f\n", iter->vertices[3].x, iter->vertices[3].y, iter->vertices[3].z);
	printf("\n");
}

void bspnode_print(bspNode* iter)
{
	if(iter->splitter!=NULL)
	{
	printf("polygon:\n");
	printf("%f,%f,%f\n", iter->splitter->vertices[0].x, iter->splitter->vertices[0].y, iter->splitter->vertices[0].z);
	printf("%f,%f,%f\n", iter->splitter->vertices[1].x, iter->splitter->vertices[1].y, iter->splitter->vertices[1].z);
	printf("%f,%f,%f\n", iter->splitter->vertices[2].x, iter->splitter->vertices[2].y, iter->splitter->vertices[2].z);
	printf("%f,%f,%f\n", iter->splitter->vertices[3].x, iter->splitter->vertices[3].y, iter->splitter->vertices[3].z);
	}
	printf("isLeaf = %d\n", iter->isLeaf);
	printf("isSolid = %d\n", iter->isSolid);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	polygon* list = NULL;
	polygon* child = NULL;

	vec3 v1 = {-1.0, -1.0, 1.0};
	vec3 verts[4];
	verts[0] = v1;
	verts[1] = v1;
	verts[2] = v1;
	verts[3] = v1;

	int a;
	for(a=0;a<4;a++)
	{
		if (list == NULL)
		{
			list = polygon_add(NULL, verts, 4);
			child = list;
		}
		else
		{
			verts[0].x = (float)a;
			child = polygon_add(child, verts, 4);
		}
	}

	polygon* iter = NULL;

	for(a=0;a<4;a++)
	{
		if(iter == NULL)
		{
			iter = list;
		}
		else
		{
			iter = iter->next;
		}

		polygon_print(iter);
	}

	polygon* splitter = selectBestSplitter(list);
	polygon_print(splitter);

	bspNode root;

	BuildBspTree(&root, list);

	bspnode_print(&root);
	bspnode_print(root.front->front->front->back);

	return 0;
}