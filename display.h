#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <SDL.h>

typedef struct display
{
	SDL_Window *sdlWindow;
	SDL_Renderer *sdlRenderer;
	SDL_Surface *screen;
	SDL_Texture *sdlTexture;
	uint32_t* frameBuffer;
	float* zbuffer;
	float w;
	float h;
}display;

int display_init(display* d, float sw, float sh);
void display_clear(display* d);
void display_refresh(display* d);
void display_destroy(display* d);

#endif // DISPLAY_H_