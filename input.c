#include "input.h"

void onKeyDownOrUp(input* in, const SDL_Event e, int down)
{
	switch(e.key.keysym.sym) {
		default:
			break;
		case SDLK_a:
			in->keys.a = down;
			break;
		case SDLK_d:
			in->keys.d = down;
		break;
		case SDLK_w:
			in->keys.w = down;
		break;
		case SDLK_s:
			in->keys.s = down;
		break;
		case SDLK_ESCAPE:
			in->keys.esc = down;
		break;
		case SDLK_1:
			in->keys.n1 = down;
		break;
		case SDLK_2:
			in->keys.n2 = down;
		break;
		case SDLK_3:
			in->keys.n3 = down;
		break;
	}
}

void onKeyDown(input* in, const SDL_Event e)
{
	onKeyDownOrUp(in, e, 1);
	switch(e.key.keysym.sym) {
		default:
			break;
	}
}

void onKeyUp(input* in, const SDL_Event e)
{
	onKeyDownOrUp(in, e, 0);
}

void onMouseMove(input* in, const SDL_Event e)
{
	int x,y;
	SDL_GetMouseState(&x,&y);
	//SDL_GetRelativeMouseState(&x,&y);
	//printf("%d, %d\n", x,y);
	in->cursor.x = x;
	in->cursor.y = y;
	in->cursor.xoffset = in->cursor.lastX - x;
    in->cursor.yoffset = in->cursor.lastY - y;
    in->cursor.lastX = x;
    in->cursor.lastY = y;
}

void HandleEvent(input* in, SDL_Event event)
{
	switch(event.type) {
		default:
			break;
		case SDL_QUIT:
			//engineRunning = 0;
			break;
		case SDL_KEYDOWN:
			onKeyDown(in, event);
			break;
		case SDL_KEYUP:
			onKeyUp(in, event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(in, event);
			in->mouseMoved = 1;
			break;
	}
}

void input_init(input* in)
{
	in->cursor.lastX = 320;
	in->cursor.lastY = 240;
	in->keys.w = 0;
	in->keys.s = 0;
	in->keys.a = 0;
	in->keys.d = 0;
	in->keys.esc = 0;
	in->keys.n1 = 0;
	in->keys.n2 = 0;
	in->keys.n3 = 0;
}

void input_poll(input* in)
{
	in->mouseMoved = 0;

	SDL_Event event;
	while(SDL_PollEvent(&event))
		HandleEvent(in, event);
}