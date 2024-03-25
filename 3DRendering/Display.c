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
	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void DrawPixel(int x, int y, uint32_t color) {
	if(x >= 0 && x < windowWidth && y < windowHeight && y >= 0)
		colorBuffer[(windowWidth * y) + x] = color;
}