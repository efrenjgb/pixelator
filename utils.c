#include "utils.h"

int vec3_project(vec3* p, vec3 v, mat4 tm)
{
	float x = tm.m[0] * v.x + tm.m[4] * v.y + tm.m[8]  * v.z + tm.m[12] * 1.0f;
	float y = tm.m[1] * v.x + tm.m[5] * v.y + tm.m[9]  * v.z + tm.m[13] * 1.0f;
	float z = tm.m[2] * v.x + tm.m[6] * v.y + tm.m[10] * v.z + tm.m[14] * 1.0f;
	float w = tm.m[3] * v.x + tm.m[7] * v.y + tm.m[11] * v.z + tm.m[15] * 1.0f;

	//printf("x: %f, y: %f, z: %f, w:%f\n", x,y,z,w);
	int cull = (-w <= z || z <= w);// || -w <= y || y <= w || -w <= x || x <= w);
	//printf("%d\n", cull);
	if(cull)
		return 0;

	x = x/w;
	y = y/w;
	z = z/w;	

	x = x/z;
	y = y/z;

	//printf("x: %f, y: %f, z: %f\n", x,y,z);
	p->x = x;
	p->y = y;
	p->z = z;

	return 1;
}

void vec3_toScreen(vec3* p, display d)
{
	p->x = ( ( p->x * 0.5f ) + 0.5f ) * d.w;
	p->y = ( ( p->y * 0.5f ) + 0.5f ) * d.h;
	// p->x = (p->x)  * d.w + d.w / 2.0f;
	// p->y = p->y * d.h + d.h / 2.0f;
	// float aspect = d.w / d.h;
	// if(aspect > 1.0)
	// {
	// 	p->x = p->x / aspect;
	// 	p->y = p->y / aspect;
	// }
	// else
	// {
	// 	p->y = p->y * aspect;
	// }
}

uint32_t color(float R, float G, float B, float A)
{
	uint32_t r = (uint32_t)(R * 255.0f);
	uint32_t g = (uint32_t)(G * 255.0f);
	uint32_t b = (uint32_t)(B * 255.0f);
	uint32_t a = (uint32_t)(A * 255.0f);

	return (a << 24) | (r << 16) | (g << 8) | b;
}

void renderBspTree(bspNode *node, vec3 pos, display dc, mat4 tM)
{
	if(node->isLeaf == 1)
		return;

	int result=ClassifyPoint(pos, node->splitter);

	if (result==CP_FRONT)
	{
		if (node->back != NULL)
			renderBspTree(node->back, pos, dc, tM);
		//lpDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,D3DFVF_LVERTEX,&Node->Splitter->VertexList[0],Node->Splitter->NumberOfVertices,&Node->Splitter->Indices[0],Node->Splitter->NumberOfIndices,NULL);
		int i;
		int faces = node->splitter->indicesCount/3;
		for (i=0;i<faces;i++)
		{
			vec3 vA = node->splitter->vertices[ node->splitter->indices[i*3]     ];
			vec3 vB = node->splitter->vertices[ node->splitter->indices[(i*3)+1] ];
			vec3 vC = node->splitter->vertices[ node->splitter->indices[(i*3)+2] ];

			vec3 pA;
			vec3 pB;
			vec3 pC;

			int a = vec3_project(&pA, vA, tM);
			if(a) vec3_toScreen(&pA,dc);
			int b = vec3_project(&pB, vB, tM);
			if(b) vec3_toScreen(&pB,dc);
			int c = vec3_project(&pC, vC, tM);
			if(c) vec3_toScreen(&pC,dc);

			float cv = 0.25f + (i % faces) * 0.75f / faces;
			//float cv = 1.0f;
			if(a&&b&&c)
				rasterizer_drawTriangle(&dc, pA, pB, pC, color(cv,cv,cv, 1.0f));
		}

		if (node->front != NULL)
			renderBspTree(node->front, pos, dc, tM);
		return;
	} // this happens if we are at back or on plane
	if(node->front != NULL) renderBspTree(node->front, pos, dc, tM);
	if(node->back != NULL) renderBspTree(node->back, pos, dc, tM);
	return;
}