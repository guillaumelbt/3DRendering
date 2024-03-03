#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool bIsRunning = false;

<<<<<<< HEAD
int width = 800;
int height = 600;
uint32_t* colorBuffer = NULL;


=======
>>>>>>> 742d033ec642cb2e0ef81198a72aba6fe06970b5
bool InitializeWindow(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error Init SDL");
		return false;
	}

<<<<<<< HEAD
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_BORDERLESS);
=======
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,800,600,SDL_WINDOW_BORDERLESS);
>>>>>>> 742d033ec642cb2e0ef81198a72aba6fe06970b5

	if (!window) {
		fprintf(stderr, "Error creating window");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);

	if(!renderer) {
		fprintf(stderr, "Error creating renderer");
		return false;
	}
	return true;

}

void Setup(void) {
<<<<<<< HEAD
	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * width * height);
=======

>>>>>>> 742d033ec642cb2e0ef81198a72aba6fe06970b5
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
	return 0;
}