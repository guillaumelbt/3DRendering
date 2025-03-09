#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <stdint.h>
#include "Vector.h"
#include "Display.h"
#include "Texture.h"

typedef struct {
	int a;
	int b;
	int c; 
	tex2 a_uv;
	tex2 b_uv;
	tex2 c_uv;
	uint32_t color;
} face;

typedef struct {
	vec4 points[3];
	tex2 texCoords[3];
	uint32_t color;
	float avgDepth;
} triangle;


void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void DrawTexturedTriangle(
	int x0, int y0, float z0, float w0, float u0, float v0,
	int x1, int y1, float z1, float w1, float u1, float v1,
	int x2, int y2, float z2, float w2, float u2, float v2,
	uint32_t* tex);


#endif

