#ifndef RASTERIZER_H_
#define RASTERIZER_H_

#include <stdint.h>
#include "vector3.h"
#include "display.h"

typedef struct point
{
	float x;
	float y;
}point;

void rasterizer_setPixel(display* dc, int x, int y, float z, uint32_t color);
//void rasterizer_setPixel(float x, float y, uint32_t color);
void rasterizer_clear();

void rasterizer_drawPoint(uint32_t color, float x, float y);
//void rasterizer_drawPoint(uint32_t color, Point2 p);
void rasterizer_drawLine(uint32_t color1, float x1, float y1, uint32_t color2, float x2, float y2);
void rasterizer_drawBLine(display* dc, vec3 point0, vec3 point1, uint32_t c);
void rasterizer_drawTriangle(display* dc, vec3 p1, vec3 p2, vec3 p3, uint32_t color);

#endif // RASTERIZER_H_