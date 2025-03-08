#include <math.h>
#include "Vector.h"

float Vec2Lenght(vec2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

vec2 Vec2Add(vec2 a, vec2 b)
{
	vec2 result = {
		a.x + b.x,
		a.y + b.y
	};
	return result;
}

vec2 Vec2Sub(vec2 a, vec2 b)
{
	vec2 result = {
		a.x - b.x,
		a.y - b.y
	};
	return result;
}

vec2 Vec2Mul(vec2 a, float f)
{
	vec2 result = {
		a.x * f,
		a.y * f
	};
	return result;
}

vec2 Vec2Div(vec2 a, float f)
{
	vec2 result = {
		a.x / f,
		a.y / f
	};
	return result;
}

float Vec2Dot(vec2 a, vec2 b)
{
	return (a.x * b.x) + (a.y * b.y);
}

float Vec3Lenght(vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 Vec3Add(vec3 a, vec3 b)
{
	vec3 result = {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};
	return result;
}

vec3 Vec3Sub(vec3 a, vec3 b)
{
	vec3 result = {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	};
	return result;
}

vec3 Vec3Mul(vec3 a, float f)
{
	vec3 result = {
		a.x * f,
		a.y * f,
		a.z * f
	};
	return result;
}

vec3 Vec3Div(vec3 a, float f)
{
	vec3 result = {
		a.x / f,
		a.y / f,
		a.z / f
	};
	return result;
}

vec3 Vec3CrossProduct(vec3 a, vec3 b)
{
	vec3 result = {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
	return result;
}

float Vec3Dot(vec3 a, vec3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

vec3 RotateX(vec3 v, float angle) {
	vec3 rotatedVector = {
		v.x,
		v.y * cos(angle) - v.z * sin(angle),
		v.y * sin(angle) + v.z * cos(angle)
	};
	return rotatedVector;
}

vec3 RotateY(vec3 v, float angle) {
	vec3 rotatedVector = {
		v.x * cos(angle) - v.z * sin(angle),
		v.y,
		v.x * sin(angle) + v.z * cos(angle)
	};
	return rotatedVector;
}

vec3 RotateZ(vec3 v, float angle) {
	vec3 rotatedVector = {
		v.x* cos(angle) - v.y * sin(angle),
		v.x * sin(angle) + v.y * cos(angle),
		v.z
	};
	return rotatedVector;
}

void Vec3Normalize(vec3* v) {
	float length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

vec3 Vec3FromVec4(vec4 v)
{
	vec3 res =
	{
		v.x, v.y, v.z
	};
	return res;
}

vec4 Vec4FromVec3(vec3 v)
{
	vec4 res =
	{
		v.x, v.y, v.z, 1.0
	};
	return res;
}