#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <stdint.h>
#include "Vector.h"
#include "Display.h"


typedef struct {
	int a;
	int b;
	int c;
	uint32_t color;
} face;

typedef struct {
	vec2 points[3];
	uint32_t color;
	float avgDepth;
} triangle;


void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

#endif

