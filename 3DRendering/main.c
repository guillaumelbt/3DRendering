#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool bIsRunning = false;
SDL_Texture* colorBufferTexture = NULL;


int width = 800;
int height = 600;
uint32_t* colorBuffer = NULL;



bool InitializeWindow(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error Init SDL");
		return false;
	}

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_BORDERLESS);

	if (!window) {
		fprintf(stderr, "Error creating window");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if(!renderer) {
		fprintf(stderr, "Error creating renderer");
		return false;
	}

	colorBufferTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ABGR8888,
		SDL_TEXTUREACCESS_STREAMING,
		width,
		height
	);
	return true;

}

void Setup(void) {

	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * width * height);

	if (!colorBuffer) {
		bIsRunning = false;
	}

}

void ProcessInput(void) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			bIsRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					bIsRunning = false;
					break;
			}
			break;
	}

}

void ClearColorBuffer(uint32_t color) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++)
		{
			colorBuffer[(width * y) + x] = color;
		}
	}
}


void RenderColorBuffer() {
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,
		colorBuffer,
		(int)(width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
}

void Update(float deltaTime) {

}

void Render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	ClearColorBuffer(0xFFFFFF00);
	SDL_RenderPresent(renderer);
}

int main(int argc, char* args[]) {	
	bIsRunning = InitializeWindow();

	Setup();

	while (bIsRunning) {
		ProcessInput();
		Update(1);
		Render();
	}

	free(colorBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}