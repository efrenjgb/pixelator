#include "rasterizer.h"

float clamp(float value) // between 0 and 1
{
	if(value < 0)
		return 0.0f;
	if(value > 1.0f)
		return 1.0f;
	return value; 
}

float interpolate(float min, float max, float gradient)
{
	return min + (max - min) * clamp(gradient);
}

float cross2D(float x0, float y0, float x1, float y1)
{
   return x0 * y1 - x1 * y0;
}

float lineSide2D(vec3 p, vec3 lineFrom, vec3 lineTo)
{
   return cross2D(p.x - lineFrom.x, p.y - lineFrom.y, lineTo.x - lineFrom.x, lineTo.y - lineFrom.y);
}

void rasterizer_setPixel(display* dc, int x, int y, float z, uint32_t color)
{
	if(x < 0 || y < 0 ||x >= dc->w || y >= dc->h)
		return;

	int idx = y * (int)dc->w + x;

	if(dc->zbuffer[idx] < z)
		return;

	dc->zbuffer[idx] = z;
	dc->frameBuffer[idx] = color;
}

void doScanLine(display* dc, int y, vec3 pa, vec3 pb, vec3 pc, vec3 pd, uint32_t color)
{
	if(y < 0 || y > dc->h)
		return;

	float gradient1 = pa.y != pb.y ? (y - pa.y) / (pb.y - pa.y) : 1;
	float gradient2 = pc.y != pd.y ? (y - pc.y) / (pd.y - pc.y) : 1;
	        
	int sx = (int)interpolate(pa.x, pb.x, gradient1);
	int ex = (int)interpolate(pc.x, pd.x, gradient2);

	float z1 = interpolate(pa.z, pb.z, gradient1);
    float z2 = interpolate(pc.z, pd.z, gradient2);

	if(sx < 0) sx = 0;
	if(ex > dc->w) ex = dc->w;

	// drawing a line from left (sx) to right (ex) 
	int x;
	for (x = sx; x < ex; x++)
	{
		float gradient = (x - sx) / (float)(ex - sx);

        float z = interpolate(z1, z2, gradient);
   //   int idx = y * (int)dc->w + x;
   //   int idx2 = y * (int)dc->w + (ex - 1);
   //   if(dc->zbuffer[idx] < -z && dc->zbuffer[idx2] < -z)
		// return;
		rasterizer_setPixel(dc, x, y, -z, color);
	}
}

void rasterizer_drawTriangle(display* dc, vec3 p1, vec3 p2, vec3 p3, uint32_t color)
{
    if (p1.y > p2.y)
    {
        vec3 temp = p2;
        p2 = p1;
        p1 = temp;
    }

    if (p2.y > p3.y)
    {
        vec3 temp = p2;
        p2 = p3;
        p3 = temp;
    }

    if (p1.y > p2.y)
    {
        vec3 temp = p2;
        p2 = p1;
        p1 = temp;
    }

    int y;

    if (cross2D(p2.x - p1.x, p2.y - p1.y, p3.x - p1.x, p3.y - p1.y) > 0)//lineSide2D(p2, p1, p3) > 0)//(dP1P2 > dP1P3)
    {
        for (y = (int)p1.y; y <= (int)p3.y; y++)
        {
            if (y < p2.y)
            {
                doScanLine(dc, y, p1, p3, p1, p2, color);
            }
            else
            {
                doScanLine(dc, y, p1, p3, p2, p3, color);
            }
        }
    }
    else
    {
        for (y = (int)p1.y; y <= (int)p3.y; y++)
        {
            if (y < p2.y)
            {
                doScanLine(dc, y, p1, p2, p1, p3, color);
            }
            else
            {
                doScanLine(dc, y, p2, p3, p1, p3, color);
            }
        }
    }
}


void rasterizer_drawBLine(display* dc, vec3 point0, vec3 point1, uint32_t c)
{
	int x0 = (int)point0.x;
	int y0 = (int)point0.y;
	int x1 = (int)point1.x;
	int y1 = (int)point1.y;
	    
	int dx = (x1 - x0) < 0 ? (x1-x0)*-1 : (x1-x0);
	int dy = (y1 - y0) < 0 ? (y1-y0)*-1 : (y1-y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		rasterizer_setPixel(dc, (unsigned int)x0, (unsigned int)y0, 10000000.0f, c);

		if ((x0 == x1) && (y0 == y1)) break;
		int e2 = 2 * err;
		if (e2 > -dy) { err -= dy; x0 += sx; }
		if (e2 < dx) { err += dx; y0 += sy; }
	}
}

void rasterizer_clear()
{

}