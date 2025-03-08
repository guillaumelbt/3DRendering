#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

typedef struct {
	float m[4][4];
} mat4x4;


mat4x4 Mat4x4Identity(void);
mat4x4 mat4x4MakeScale(float sx, float sy, float sz);
mat4x4 mat4x4MakeTranslation(float tx, float ty, float tz);
mat4x4 mat4x4RotateX(float angle);
mat4x4 mat4x4RotateY(float angle);
mat4x4 mat4x4RotateZ(float angle);
mat4x4 mat4x4MakePerspective(float fov, float aspectRatio, float zNear, float zFar);
vec4 mat4x4MultVec4Project(mat4x4 projectionMatrix, vec4 v);
vec4 mat4x4MultVec4(mat4x4 m, vec4 v);
mat4x4 mat4x4Mult(mat4x4 a, mat4x4 b);
#endif