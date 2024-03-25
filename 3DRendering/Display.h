#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

extern SDL_Texture* colorBufferTexture;
extern uint32_t* colorBuffer;

extern int windowWidth;
extern int windowHeight;

bool InitializeWindow(void);
void DrawGrid(void);
void DrawRectangle(int x, int y, int width, int height, uint32_t color);
void RenderColorBuffer(void);
void ClearColorBuffer(uint32_t color);
void DestroyWindow(void);

#endif