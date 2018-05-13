#ifndef UTILS_H_
#define UTILS_H_

#include "vector3.h"
#include "matrix.h"
#include "display.h"
#include "rasterizer.h"
#include "bsp.h"

int vec3_project(vec3* p, vec3 v, mat4 tm);
void vec3_toScreen(vec3* p, display d);
uint32_t color(float R, float G, float B, float A);
void renderBspTree(bspNode *node, vec3 pos, display dc, mat4 tM);

#endif // UTILS_H_