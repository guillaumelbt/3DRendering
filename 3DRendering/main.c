#include "Display.h"
#include "Vector.h"

bool bIsRunning = false;


#define N_POINTS (9 * 9 * 9)

vec3 cubePoints[N_POINTS];
vec2 projectedPoints[N_POINTS];

vec3 cameraPosition = { 0 , 0 , -5 };

vec3 cubeRotation = { 0 , 0 , 0 };

float fovFactor = 640;

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

	int pointCount = 0;
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3 newPoint = { x , y , z };
				cubePoints[pointCount++] = newPoint;
			}
		}
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


vec2 Project(vec3 point) {
	vec2 projectedPoint = { (fovFactor * point.x) / point.z, (fovFactor * point.y) / point.z};
	return projectedPoint;
}

void Update(float deltaTime) {
	cubeRotation.x += 0.01;
	cubeRotation.y += 0.01;
	cubeRotation.z += 0.01;


	for (int i = 0; i < N_POINTS; i++) {
		vec3 point = cubePoints[i];

		vec3 transformedPoint = RotateX(point, cubeRotation.x);
		transformedPoint = RotateY(transformedPoint, cubeRotation.y);
		transformedPoint = RotateZ(transformedPoint, cubeRotation.z);

		transformedPoint.z -= cameraPosition.z;

		projectedPoints[i] = Project(transformedPoint);
	}
}

void Render(void) {
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);

	DrawGrid();
	for (int i = 0; i < N_POINTS; i++) {
		vec2 projectedPoint = projectedPoints[i];
		DrawRectangle(
			projectedPoint.x + windowWidth/2, 
			projectedPoint.y + windowHeight/2, 
			4, 
			4, 
			0xFF33FF33);
	}
	
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