#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

enum cull_method
{
	CULL_NONE,
	CULL_BACKFACE
} cullMethod;

enum render_method
{
	RENDER_VERTEX = 1 << 0,
	RENDER_WIRE = 1 << 1,
	RENDER_TRIANGLE_FILLED = 1 << 2,
	RENDER_TRIANGLE_TEXTURED = 1 << 3
} renderMethod;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern SDL_Texture* colorBufferTexture;
extern uint32_t* colorBuffer;

extern float* zBuffer;

extern int windowWidth;
extern int windowHeight;

bool InitializeWindow(void);
void DrawGrid(void);
void DrawPixel(int x, int y, uint32_t color);
void DrawRectangle(int x, int y, int width, int height, uint32_t color);
void RenderColorBuffer(void);
void ClearColorBuffer(uint32_t color);
void ClearZBuffer();
void DestroyWindow(void);
void DrawLine(int x0, int y0, int x1, int y1, uint32_t color);

#endif