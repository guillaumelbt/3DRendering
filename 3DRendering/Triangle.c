#include "Triangle.h"

void IntSwap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

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
	if (y0 > y1) { IntSwap(&y0, &y1); IntSwap(&x0, &x1); }
	if (y1 > y2) { IntSwap(&y1, &y2); IntSwap(&x1, &x2); }
	if (y0 > y1) { IntSwap(&y0, &y1); IntSwap(&x0, &x1); }


	if(y1 == y2)
		FillFlatBottomTriangle(x0, y0, x1, y1, x2, y2, color);
	else if(y0 == y1)
		FillFlatTopTriangle(x0, y0, x1, y1, x2, y2, color);
	else
	{
		int My = y1;
		int Mx = x0 + ((x2 - x0) * (y1 - y0)) / (y2 - y0);

		FillFlatBottomTriangle(x0, y0, x1, y1, Mx, My, color);

		FillFlatTopTriangle(x1, y1, Mx, My, x2, y2, color);
	}
}

void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	DrawLine(x0, y0, x1, y1, color);
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x0, y0, color);

}