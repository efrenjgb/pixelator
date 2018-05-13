#ifndef INPUT_H_
#define INPUT_H_

#include <stdint.h>
#include "vector3.h"
#include "display.h"

typedef struct key
{
	int w;
	int s;
	int a;
	int d;
	int esc;
	int n1;
	int n2;
	int n3;
}key;

typedef struct mouse
{
	int x;
	int y;
	int lastX;
	int lastY;
	int xoffset;
	int yoffset;
}mouse;

typedef struct input
{
	key keys;
	mouse cursor;
	int mouseMoved;
}input;

void input_init(input* in);
void input_poll(input* in);
void input_clear();

#endif // INPUT_H_