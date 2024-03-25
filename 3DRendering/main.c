#include "Display.h"
#include "Vector.h"
#include "Mesh.h"

bool bIsRunning = false;

float previousFrameTime = 0;

triangle trianglesToRender[N_MESH_FACES];

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

	/*int pointCount = 0;
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3 newPoint = { x , y , z };
				cubePoints[pointCount++] = newPoint;
			}
		}
	}*/
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

	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}
	previousFrameTime = SDL_GetTicks();

	cubeRotation.x += 0.01;
	cubeRotation.y += 0.01;
	cubeRotation.z += 0.01;

	for (int i = 0; i < N_MESH_FACES; i++)
	{
		face curFace = meshFaces[i];
		vec3 faceVertices[3];
		faceVertices[0] = meshVertices[curFace.a - 1];
		faceVertices[1] = meshVertices[curFace.b - 1];
		faceVertices[2] = meshVertices[curFace.c - 1];
		triangle projectedTriangle;
		for (int j = 0; j < 3; j++) {
			vec3 transformedVertex = faceVertices[j];

			transformedVertex = RotateX(transformedVertex, cubeRotation.x);
			transformedVertex = RotateY(transformedVertex, cubeRotation.y);
			transformedVertex = RotateZ(transformedVertex, cubeRotation.z);

			transformedVertex.z -= cameraPosition.z;

			vec2 projectedVertex = Project(transformedVertex);

			projectedVertex.x += windowWidth / 2;
			projectedVertex.y += windowHeight / 2;

			projectedTriangle.points[j] = projectedVertex;
		}
		trianglesToRender[i] = projectedTriangle;
	}

	/*for (int i = 0; i < n_points; i++) {
		vec3 point = cubepoints[i];
		vec3 transformedpoint = rotatex(point, cuberotation.x);
		transformedpoint = rotatey(transformedpoint, cuberotation.y);
		transformedpoint = rotatez(transformedpoint, cuberotation.z);
		transformedpoint.z -= cameraposition.z;
		projectedpoints[i] = project(transformedpoint);
	}*/
}

void Render(void) {
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);

	DrawGrid();

	for (int i = 0; i < N_MESH_FACES; i++) {
		triangle tri = trianglesToRender[i];
		//vec2 projectedPoint = projectedPoints[i];
		DrawRectangle(tri.points[0].x, tri.points[0].y,3, 3, 0xFF33FF33);
		DrawRectangle(tri.points[1].x, tri.points[1].y, 3, 3, 0xFF33FF33);
		DrawRectangle(tri.points[2].x, tri.points[2].y, 3, 3, 0xFF33FF33);
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