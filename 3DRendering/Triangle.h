#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"

typedef struct {
	int a;
	int b;
	int c;
} face;

typedef struct {
	vec2 points[3];
} triangle;
#endif

