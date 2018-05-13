// sdl2 sudo apt-get install libsdl2-dev

#include <stdio.h>
#include <math.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "display.h"
#include "input.h"
#include "vector3.h"
#include "matrix.h"
#include "rasterizer.h"
#include "camera.h"
#include "mesh.h"
#include "collision.h"
#include "utils.h"

int engineRunning = 1;

float sw = 640.0f;
float sh = 480.0f;

float swh = 320.0f;
float shh = 240.0f;

vec3 front = {0.0f, 0.0f, -1.0f};
const int show_vertices = 0x0001;
const int show_wireframe = 0x0010;
const int show_triangles = 0x0100;

int displayFlag;

int main()
{
	display dc;
	input istate;

	display_init(&dc, sw, sh);
	input_init(&istate);

	//SDL_SetRelativeMouseMode(1);
	//SDL_ShowCursor(SDL_DISABLE);

	mesh m1;
	mesh_init(&m1, "cube6.babylon");

	mesh m2;
	mesh_init(&m2, "monkey.babylon");

	mesh_map_init("file.map");

	mesh meshes[2];
	meshes[0] = m1;
	meshes[1] = m2;

	int meshCount = 2;

	displayFlag = show_triangles;

	camera cam;
	vec3 eye = {0.0f, 0.0f, 20.0f};
	vec3 tar = {0.0f, 0.0f, 0.0f};

	camera_init(&cam, eye, tar, 45.0f, 1.0f, 1000.0f, 0.3f);

	Uint32 startclock;
	Uint32 deltaclock;
	Uint32 currentFPS;

	startclock = SDL_GetTicks();

	char fps[20];

	float lowy  = 0.0f;
	float lx = 0.0f;
	float hx = 0.0f;
	float lz = 0.0f;
	float hz = 0.0f;

	int j;
	for (j=0;j<m1.vertexCount;j++)
	{
		if(m1.vertices[j].y < lowy)
			lowy = m1.vertices[j].y;
		if(m1.vertices[j].x < lx)
			lx = m1.vertices[j].x;
		if(m1.vertices[j].z < lz)
			lz = m1.vertices[j].z;
		if(m1.vertices[j].x > hx)
			hx = m1.vertices[j].x;
		if(m1.vertices[j].z > hz)
			hz = m1.vertices[j].z;
	}		

	printf("Low Y: %f\n", lowy);
	printf("Low X: %f\n", lx);
	printf("Low Z: %f\n", hx);
	printf("High X: %f\n", lz);
	printf("High Z: %f\n", hz);

	float thold = 8.0f;

	bspNode* tree = initBsp();

	while(engineRunning)
	{
		//clear frame buffer
		deltaclock = SDL_GetTicks() - startclock;
		startclock = SDL_GetTicks();
		
		if ( deltaclock != 0 )
			currentFPS = 1000 / deltaclock;
		sprintf(fps, "FPS: %d", currentFPS);

		input_poll(&istate);

		cam.speed = 0.05f * deltaclock;

		camera_doMovement(&cam, istate);

		if(istate.cursor.x < 5 || istate.cursor.x > 635 || istate.cursor.y < 5 || istate.cursor.y > 475)
		{
			istate.cursor.lastX = swh;
			istate.cursor.lastY = shh;
			SDL_WarpMouseInWindow(dc.sdlWindow, swh, shh);
		}

		if(istate.keys.esc){
			engineRunning = 0;
		}
		if(istate.keys.n1){
			displayFlag = show_vertices;

		}
		if(istate.keys.n2){
			displayFlag = show_wireframe;
		}
		if(istate.keys.n3){
			displayFlag = show_triangles;
		}

		display_clear(&dc);

		vec3 up = {0.0f, 1.0f, 0.0f};

		mat4 viewMatrix;
		mat4_lookAtLH(&viewMatrix, cam.position, cam.target, up);

		mat4 projectionMatrix;
		mat4_projectionFov(&projectionMatrix, cam.fov, sw, sh, cam.znear, cam.zfar);

		int i,j;
		for(i=0;i<meshCount;i++)
		{
			mesh m = meshes[i];

			vec3 pos = {0.0f, 2.0f*i, -8.0f*i};
			mat4 worldMatrix;
			mat4_translation(&worldMatrix, pos);

			mat4 worldViewMatrix;
			mat4 transformMatrix;

			mat4_multiply(&worldViewMatrix, worldMatrix, viewMatrix);
			mat4_multiply(&transformMatrix, worldViewMatrix, projectionMatrix);

			if(displayFlag & show_vertices)
			for (j=0;j<m.vertexCount;j++)
			{
				vec3 p;
				if(vec3_project(&p, m.vertices[j], transformMatrix))
				{
					vec3_toScreen(&p, dc);
					rasterizer_setPixel(&dc, p.x, p.y, 1000.0f, color(0.0f, 1.0f, 0.0f, 1.0f));
				}
			}		

			if(displayFlag & show_wireframe)
			{
				for(j=0;j<m.faceCount;j++)
				{
					vec3 vA = m.vertices[m.faces[j].a];
					vec3 vB = m.vertices[m.faces[j].b];
					vec3 vC = m.vertices[m.faces[j].c];

					vec3 pA;
					vec3 pB;
					vec3 pC;

					int a = vec3_project(&pA, vA, transformMatrix);
					if(a) vec3_toScreen(&pA,dc);

					int b = vec3_project(&pB, vB, transformMatrix);
					if(b) vec3_toScreen(&pB,dc);

					int c = vec3_project(&pC, vC, transformMatrix);
					if(c) vec3_toScreen(&pC,dc);

					if(a && b)
						rasterizer_drawBLine(&dc, pA, pB, color(0.5f,0.5f,0.5f, 1.0f));
					if(b && c)
						rasterizer_drawBLine(&dc, pB, pC, color(0.5f,0.5f,0.5f, 1.0f));
					if(c && a)
						rasterizer_drawBLine(&dc, pC, pA, color(0.5f,0.5f,0.5f, 1.0f));
				}
			}

			if(displayFlag & show_triangles)
			{
				for(j=0;j<m.faceCount;j++)
				{
					vec3 vA = m.vertices[m.faces[j].a];
					vec3 vB = m.vertices[m.faces[j].b];
					vec3 vC = m.vertices[m.faces[j].c];

					vec3 pA;
					vec3 pB;
					vec3 pC;

					int a = vec3_project(&pA, vA, transformMatrix);
					if(a) vec3_toScreen(&pA, dc);

					int b = vec3_project(&pB, vB, transformMatrix);
					if(b) vec3_toScreen(&pB, dc);

					int c = vec3_project(&pC, vC, transformMatrix);
					if(c) vec3_toScreen(&pC, dc);

					float cv = 0.25f + (j % m.faceCount) * 0.75f / m.faceCount;

					if(a && b && c)
						rasterizer_drawTriangle(&dc, pA, pB, pC, color(cv, cv, cv, 1.0f));
				}
			}
		}

		vec3 pos = {0.0f, -2.0f, 0.0f};
		mat4 worldMatrix;
		mat4_translation(&worldMatrix, pos);

		mat4 worldViewMatrix;
		mat4 transformMatrix;

		mat4_multiply(&worldViewMatrix, worldMatrix, viewMatrix);
		mat4_multiply(&transformMatrix, worldViewMatrix, projectionMatrix);
		//renderBspTree(tree, cam.position, dc, transformMatrix);

		//display frame buffer
		display_refresh(&dc);
		//engineRunning = 0;
		//SDL_Delay(10);
	}

	display_destroy(&dc);

	return 0;
}