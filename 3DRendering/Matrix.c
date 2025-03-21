#include <math.h>
#include "Matrix.h"

mat4x4 Mat4x4Identity(void)
{
	mat4x4 m = { {
		{ 1, 0, 0, 0},
		{ 0, 1, 0, 0},
		{ 0, 0, 1, 0},
		{ 0, 0, 0, 1}
	} };
	return m;
}

mat4x4 mat4x4MakeScale(float sx, float sy, float sz)
{
	mat4x4 m = Mat4x4Identity();
	m.m[0][0] = sx;
	m.m[1][1] = sy;
	m.m[2][2] = sz;
	return m;
}

mat4x4 mat4x4MakeTranslation(float tx, float ty, float tz)
{
	mat4x4 m = Mat4x4Identity();
	m.m[0][3] = tx;
	m.m[1][3] = ty;
	m.m[2][3] = tz;
	return m;
}

mat4x4 mat4x4RotateX(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4x4 m = Mat4x4Identity();
	m.m[1][1] = c;
	m.m[1][2] = -s;
	m.m[2][1] = s;
	m.m[2][2] = c;
	return m;
}

mat4x4 mat4x4RotateY(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4x4 m = Mat4x4Identity();
	m.m[0][0] = c;
	m.m[0][2] = s;
	m.m[2][0] = -s;
	m.m[2][2] = c;
	return m;
}

mat4x4 mat4x4RotateZ(float angle)
{
	float c = cos(angle);
	float s = sin(angle);
	mat4x4 m = Mat4x4Identity();

	m.m[0][0] = c;
	m.m[0][1] = -s;
	m.m[1][0] = s;
	m.m[1][1] = c;
	return m;
}

vec4 mat4x4MultVec4(mat4x4 m, vec4 v)
{
	vec4 res;
	res.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
	res.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
	res.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
	res.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
	return res;
}

mat4x4 mat4x4Mult(mat4x4 a, mat4x4 b)
{
	mat4x4 m;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m.m[i][j] = a.m[i][0] * b.m[0][j] + a.m[i][1] * b.m[1][j] + a.m[i][2] * b.m[2][j] + a.m[i][3] * b.m[3][j];
		}
	}
	return m;
}

mat4x4 mat4x4MakePerspective(float fov, float aspectRatio, float zNear, float zFar)
{
	mat4x4 m = { {{0}} };
	m.m[0][0] = 1 / (aspectRatio * tan(fov / 2));
	m.m[1][1] = 1 / tan(fov / 2);
	m.m[2][2] = zFar / (zFar - zNear);
	m.m[2][3] = (-zFar * zNear) / (zFar - zNear);
	m.m[3][2] = 1.0;

	return m;
}


vec4 mat4x4MultVec4Project(mat4x4 projectionMatrix, vec4 v)
{
	vec4 res = mat4x4MultVec4(projectionMatrix, v);

	if (res.w != 0.0)
	{
		res.x /= res.w;
		res.y /= res.w;
		res.z /= res.w;
	}
	return res;
}

mat4x4 mat4x4LookAt(vec3 e, vec3 target, vec3 up)
{
	vec3 z = Vec3Sub(target, e);
	Vec3Normalize(&z);
	vec3 x = Vec3CrossProduct(up, z);
	Vec3Normalize(&x);
	vec3 y = Vec3CrossProduct(z, x);

	mat4x4 viewMatrix = 
	{ 
		{
			{ x.x, x.y, x.z, -Vec3Dot(x, e) },
			{ y.x, y.y, y.z, -Vec3Dot(y, e) },
			{ z.x, z.y, z.z, -Vec3Dot(z, e) },
			{ 0, 0, 0, 1 }
		}	
	};
	return viewMatrix;
}