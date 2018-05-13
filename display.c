#include "display.h"

int display_init(display* d, float sw, float sh)
{
    // initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "SDL_Init failed\n");
		return 1;
	}

	d->sdlWindow = SDL_CreateWindow("Pixelator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sw, sh, SDL_WINDOW_OPENGL);

	d->sdlRenderer = SDL_CreateRenderer(d->sdlWindow, -1, 0);

	d->screen = SDL_CreateRGBSurface(0, sw, sh, 32,	0x00FF0000,	0x0000FF00,	0x000000FF,	0xFF000000);
	if(!d->screen) {
		SDL_Quit();
		fprintf(stderr, "SDL_CreateRGBSurface failed\n");
		return 1;
	}	

	d->sdlTexture = SDL_CreateTexture(d->sdlRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, sw, sh);

	d->w = sw;
	d->h = sh;
	d->frameBuffer = (uint32_t*)d->screen->pixels;

	d->zbuffer = malloc(sizeof(float) * sw * sh);
	
	//memset(d->zbuffer, 9999999999.0f, sizeof(float) * sw * sh);

	return 0;
}

void display_clear(display* d)
{
	memset(d->frameBuffer, 0, sizeof(uint32_t) * d->w * d->h);
	//memset(d->zbuffer, FLT_MAX, sizeof(float) * d->w * d->h);

	int i;
	int size = d->w * d->h;
	for(i=0;i<size;i++)
	{
		d->zbuffer[i] = FLT_MAX;
		//printf("%f", d->zbuffer[i]);
	}
	//printf("%d\n", sizeof(float));
}

void display_refresh(display* d)
{
	SDL_UpdateTexture(d->sdlTexture, NULL, d->screen->pixels, d->screen->pitch);
	SDL_RenderClear(d->sdlRenderer);
	SDL_RenderCopy(d->sdlRenderer, d->sdlTexture, NULL, NULL);
	SDL_RenderPresent(d->sdlRenderer);
}

void display_destroy(display* d)
{
	SDL_DestroyWindow(d->sdlWindow);
	SDL_Quit();
}