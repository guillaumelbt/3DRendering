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

typedef struct {
	float x;
	float y;
	float z;
	float w;
} vec4;

float Vec2Lenght(vec2 v);
vec2 Vec2Add(vec2 a, vec2 b);
vec2 Vec2Sub(vec2 a, vec2 b);
vec2 Vec2Mul(vec2 a, float f);
vec2 Vec2Div(vec2 a, float f);
float Vec2Dot(vec2 a, vec2 b);

float Vec3Lenght(vec3 v);
vec3 Vec3Add(vec3 a, vec3 b);
vec3 Vec3Sub(vec3 a, vec3 b);
vec3 Vec3Mul(vec3 a, float f);
vec3 Vec3Div(vec3 a, float f);
vec3 Vec3CrossProduct(vec3 a, vec3 b);
float Vec3Dot(vec3 a, vec3 b);
vec3 RotateX(vec3 v, float angle);
vec3 RotateY(vec3 v, float angle);
vec3 RotateZ(vec3 v, float angle);
void Vec3Normalize(vec3* v);
vec3 Vec3FromVec4(vec4 v);
vec2 Vec2FromVec4(vec4 v);
vec4 Vec4FromVec3(vec3 v);
#endif
