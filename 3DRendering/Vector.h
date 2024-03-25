#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x;
	float y;
} vec2;


typedef struct {
	float x;
	float y;
	float z;
} vec3;

vec3 RotateX(vec3 v, float angle);
vec3 RotateY(vec3 v, float angle);
vec3 RotateZ(vec3 v, float angle);

#endif
