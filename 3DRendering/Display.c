#include "Display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Texture* colorBufferTexture = NULL;
uint32_t* colorBuffer = NULL;

int windowWidth = 800;
int windowHeight = 600;

bool InitializeWindow(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error Init SDL");
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_BORDERLESS);

	if (!window) {
		fprintf(stderr, "Error creating window");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if (!renderer) {
		fprintf(stderr, "Error creating renderer");
		return false;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	return true;

}

void ClearColorBuffer(uint32_t color) {
	for (int y = 0; y < windowHeight; y++) {
		for (int x = 0; x < windowWidth; x++)
		{
			colorBuffer[(windowWidth * y) + x] = color;
		}
	}
}

void DrawGrid() {
	for (int y = 0; y < windowHeight; y++) {
		for (int x = 0; x < windowWidth; x++)
		{
			if (x % 10 == 0 || y % 10 == 0) {
				DrawPixel(x,y, 0xFF333333);
			}
		}
	}
}

void DrawRectangle(int x, int y, int width, int height, uint32_t color) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
		{
			int curX = x + i;
			int curY = y + j;
			DrawPixel(curX, curY, color);
		}
	}
}

void RenderColorBuffer() {
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,
		colorBuffer,
		(int)(windowWidth * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void DestroyWindow(void) {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void DrawPixel(int x, int y, uint32_t color) {
	if(x >= 0 && x < windowWidth && y < windowHeight && y >= 0)
		colorBuffer[(windowWidth * y) + x] = color;
}

void DrawLine(int x0, int y0, int x1, int y1, uint32_t color) {
	int deltaX = (x1 - x0);
	int deltaY = (y1 - y0);

	int sideLength = abs(deltaX) >= abs(deltaY) ? abs(deltaX) : abs(deltaY);

	float xInc = deltaX / (float)sideLength;
	float yInc = deltaY / (float)sideLength;

	float curX = x0;
	float curY = y0;

	for (size_t i = 0; i < sideLength; i++)
	{
		DrawPixel(round(curX), round(curY), color);
		curX += xInc;
		curY += yInc;
	}
}

void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color) {
	DrawLine(x0, y0, x1, y1, color);
	DrawLine(x1, y1, x2, y2, color);
	DrawLine(x2, y2, x0, y0, color);

}