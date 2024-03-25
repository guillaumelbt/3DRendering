#include "Display.h"


bool bIsRunning = false;


void Setup(void) {

	colorBufferTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		windowWidth,
		windowHeight
	);

	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);

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


void Update(float deltaTime) {

}

void Render(void) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	DrawGrid();
	DrawRectangle(300, 200, 400, 250, 0xFF33FF33);
	RenderColorBuffer();
	ClearColorBuffer(0xFF000000);
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

	DestroyWindow();
	return 0;
}