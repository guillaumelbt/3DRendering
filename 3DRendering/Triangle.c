#include "Triangle.h"
#define Swap(a, b, type) \
    do { \
        type tmp = *(a); \
        *(a) = *(b); \
        *(b) = tmp; \
    } while (0)


void FillFlatBottomTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	if (y1 == y0 || y2 == y0) return;
	float invSlope1 = (float)(x1 - x0) / (y1 - y0);
	float invSlope2 = (float)(x2 - x0) / (y2 - y0);


	float xStart, xEnd;
	xStart = xEnd = x0;
	for (int y = y0; y <= y2; y++)
	{
		DrawLine(xStart, y, xEnd, y,color);
		xStart += invSlope1;
		xEnd += invSlope2;
	}
}

void FillFlatTopTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	if (y2 == y0 || y2 == y1) return;
	float invSlope1 = (float)(x2 - x0) / (y2 - y0);
	float invSlope2 = (float)(x2 - x1) / (y2 - y1);

	float xStart, xEnd;
	xStart = xEnd = x2;
	
	for (int y = y2; y >= y0; y--)
	{
		DrawLine(xStart, y, xEnd, y, color);
		xStart -= invSlope1;
		xEnd -= invSlope2;
	}
}

void DrawFilledTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	//Sort vertices
	if (y0 > y1) { Swap(&y0, &y1,int); Swap(&x0, &x1, int); }
	if (y1 > y2) { Swap(&y1, &y2, int); Swap(&x1, &x2, int); }
	if (y0 > y1) { Swap(&y0, &y1, int); Swap(&x0, &x1, int); }


	if(y1 == y2)
		FillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
	else if(y0 == y1)
		FillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
	else
	{
		int My = y1;
		int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

		FillFlatBottomTriangle(x0, y0, x1, y1, Mx, My, color);

		FillFlatTopTriangle(x1, y1, Mx, My, x2, y2, color);
	}
}

void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	DrawLine(x0, y0, x1, y1, color);
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x0, y0, color);

}

vec3 BarycentricWeight(vec2 a, vec2 b, vec2 c, vec2 p) {
	vec2 ac = Vec2Sub(c, a);
	vec2 ab = Vec2Sub(b, a);
	vec2 ap = Vec2Sub(p, a);
	vec2 pc = Vec2Sub(c, p);
	vec2 pb = Vec2Sub(b, p);

	float abcAreaParallelogram = (ac.x * ab.y - ac.y * ab.x); 

	float alpha = (pc.x * pb.y - pc.y * pb.x) / abcAreaParallelogram;

	float beta = (ac.x * ap.y - ac.y * ap.x) / abcAreaParallelogram;

	float gamma = 1 - alpha - beta;

	vec3 weights = { alpha, beta, gamma };
	return weights;
}

void DrawTexel(int x, int y, uint32_t* tex,vec4 a, vec4 b, vec4 c, tex2 a_uv, tex2 b_uv, tex2 c_uv) {
	vec2 p = { x, y };
	vec3 weights = BarycentricWeight(Vec2FromVec4(a), Vec2FromVec4(b), Vec2FromVec4(c), p);

	float alpha = weights.x;
	float beta = weights.y;
	float gamma = weights.z;

	float interpolatedU, interpolatedV, interpolatedReciprocalW;

	interpolatedU = (a_uv.u / a.w) * alpha + (b_uv.u / b.w) * beta + (c_uv.u / c.w) * gamma;
	interpolatedV = (a_uv.v / a.w) * alpha + (b_uv.v / b.w) * beta + (c_uv.v / c.w) * gamma;

	interpolatedReciprocalW = (1 / a.w) * alpha + (1 / b.w) * beta + (1 / c.w) * gamma;

	interpolatedU /= interpolatedReciprocalW;
	interpolatedV /= interpolatedReciprocalW;

	int xTex = abs((int)(interpolatedU * texWidth)) % texWidth;
	int yTex = abs((int)(interpolatedV * texHeight)) % texHeight;

	interpolatedReciprocalW = 1.0 - interpolatedReciprocalW;

	if (zBuffer[(windowWidth * y) + x] > interpolatedReciprocalW)
	{
		DrawPixel(x, y, tex[(texWidth * yTex) + xTex]);

		zBuffer[(windowWidth * y) + x] = interpolatedReciprocalW;
	}
}

void DrawTexturedTriangle(
	int x0, int y0, float z0, float w0, float u0, float v0,
	int x1, int y1, float z1, float w1, float u1, float v1,
	int x2, int y2, float z2, float w2, float u2, float v2,
	uint32_t* tex)
{
	if (y0 > y1) 
	{ 
		Swap(&y0, &y1, int); 
		Swap(&x0, &x1, int); 
		Swap(&z0, &z1, float);
		Swap(&w0, &w1, float);
		Swap(&u0, &u1, float);
		Swap(&v0, &v1, float);
	}
	if (y1 > y2) 
	{ 
		Swap(&y1, &y2, int);
		Swap(&x1, &x2, int);
		Swap(&z1, &z2, float);
		Swap(&w1, &w2, float);
		Swap(&u1, &u2, float);
		Swap(&v1, &v2, float);
	}
	if (y0 > y1) 
	{ 
		Swap(&y0, &y1, int);
		Swap(&x0, &x1, int); 
		Swap(&z0, &z1, float);
		Swap(&w0, &w1, float);
		Swap(&u0, &u1, float);
		Swap(&v0, &v1, float);
	}

	v0 = 1.0 - v0;
	v1 = 1.0 - v1;
	v2 = 1.0 - v2;

	vec4 a = { x0, y0, z0, w0};
	vec4 b = { x1, y1, z1, w1};
	vec4 c = { x2, y2, z2, w2};
	tex2 a_uv = { u0, v0 };
	tex2 b_uv = { u1, v1 };
	tex2 c_uv = { u2, v2 };

	float invSlope1 = 0;
	float invSlope2 = 0;

	if (y1 - y0 != 0) invSlope1 = (float)(x1 - x0) / abs(y1 - y0);
	if (y2 - y0 != 0) invSlope2 = (float)(x2 - x0) / abs(y2 - y0);

	if (y1 - y0 != 0) 
	{
		for (int y = y0; y <= y1; y++) 
		{
			int x_start = x1 + (y - y1) * invSlope1;
			int x_end = x0 + (y - y0) * invSlope2;

			if (x_end < x_start) 
			{
				Swap(&x_start, &x_end,int);
			}

			for (int x = x_start; x < x_end; x++) 
			{
				DrawTexel(x, y, tex, a, b, c, a_uv, b_uv, c_uv);
			}
		}
	}

	invSlope1 = 0;
	invSlope2 = 0;

	if (y2 - y1 != 0) invSlope1 = (float)(x2 - x1) / abs(y2 - y1);
	if (y2 - y0 != 0) invSlope2 = (float)(x2 - x0) / abs(y2 - y0);

	if (y2 - y1 != 0) {
		for (int y = y1; y <= y2; y++) 
		{
			int x_start = x1 + (y - y1) * invSlope1;
			int x_end = x0 + (y - y0) * invSlope2;

			if (x_end < x_start) 
			{
				Swap(&x_start, &x_end,int);
			}

			for (int x = x_start; x < x_end; x++) 
			{
				DrawTexel(x, y, tex, a, b, c, a_uv, b_uv, c_uv);
			}
		}
	}
}