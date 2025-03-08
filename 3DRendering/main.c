#include "Display.h"
#include "Vector.h"
#include "Mesh.h"
#include "array.h"
#include "Matrix.h"

triangle* trianglesToRender = NULL;

bool bIsRunning = false;

float previousFrameTime = 0;

//triangle trianglesToRender[N_MESH_FACES];

vec3 cameraPosition = { 0 , 0 , 0 };
mat4x4 projectionMatrix;

void Setup(void) {

	renderMethod |= RENDER_WIRE; 
	//renderMethod |= RENDER_TRIANGLE_FILLED;
	//cullMethod = CULL_BACKFACE;

	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);

	colorBufferTexture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		windowWidth,
		windowHeight
	);

	float fov = M_PI / 3.0;
	float aspectRatio = (float)windowWidth / (float)windowHeight;
	float zNear = 0.1;
	float zFar = 100.0;

	projectionMatrix = mat4x4MakePerspective(fov,aspectRatio,zNear,zFar);

	if (!colorBuffer) {
		bIsRunning = false;
	}

	//LoadObjFileData("Assets/f22.obj");
	LoadCubeMeshData();
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

void Update(void) {

	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - previousFrameTime);

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
		SDL_Delay(timeToWait);
	}

	trianglesToRender = NULL;

	previousFrameTime = SDL_GetTicks();

	mesh.rotation.x += 0.01;
	/*mesh.rotation.y += 0.01;
	mesh.rotation.z += 0.01;*/
	/*mesh.scale.x += 0.002;
	mesh.scale.y += 0.002;
	mesh.scale.z += 0.002;
	mesh.translation.x += 0.01;*/
	mesh.translation.z = 5.0;

	mat4x4 scaleMatrix = mat4x4MakeScale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
	mat4x4 translationMatrix = mat4x4MakeTranslation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
	mat4x4 xRotationMatrix = mat4x4RotateX(mesh.rotation.x);
	mat4x4 yRotationMatrix = mat4x4RotateY(mesh.rotation.y);
	mat4x4 zRotationMatrix = mat4x4RotateZ(mesh.rotation.z);


	int numFaces = array_length(mesh.faces);

	for (int i = 0; i < numFaces; i++)
	{
		face meshFace = mesh.faces[i];

		//printf_s("%d\n", mesh.faces[i].a);

		vec3 faceVertices[3];
		faceVertices[0] = mesh.vertices[meshFace.a - 1];
		faceVertices[1] = mesh.vertices[meshFace.b - 1];
		faceVertices[2] = mesh.vertices[meshFace.c - 1];

		
		vec4 transformedVertices[3];

		for (int j = 0; j < 3; j++) {
			vec4 transformedVertex = Vec4FromVec3(faceVertices[j]);


			mat4x4 worldMatrix = Mat4x4Identity();

			worldMatrix = mat4x4Mult(scaleMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(zRotationMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(yRotationMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(xRotationMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(translationMatrix, worldMatrix);

			transformedVertex = mat4x4MultVec4(worldMatrix, transformedVertex);

			//transformedVertex.z += 5;

			transformedVertices[j] = transformedVertex;
		}

		if (cullMethod == CULL_BACKFACE)
		{
			vec3 a = Vec3FromVec4(transformedVertices[0]);
			vec3 b = Vec3FromVec4(transformedVertices[1]);
			vec3 c = Vec3FromVec4(transformedVertices[2]);

			vec3 ab = Vec3Sub(b, a);
			vec3 ac = Vec3Sub(c, a);
			Vec3Normalize(&ab);
			Vec3Normalize(&ac);


			vec3 normal = Vec3CrossProduct(ab, ac);
			Vec3Normalize(&normal);

			vec3 cameraRay = Vec3Sub(a, cameraPosition);
			float dot = Vec3Dot(normal, cameraRay);

			if (dot > 0)
				continue;
		}

		vec4 projectedPoints[3];

		for (int j = 0; j < 3; j++) {
			projectedPoints[j] = mat4x4MultVec4Project(projectionMatrix,transformedVertices[j]);

			projectedPoints[j].x *= windowWidth / 2.0;
			projectedPoints[j].y *= windowHeight / 2.0;
			
			projectedPoints[j].x += windowWidth / 2.0;
			projectedPoints[j].y += windowHeight / 2.0;
		}

		float avgDepth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;

		triangle projectedTriangle =
		{
			{
				{ projectedPoints[0].x, projectedPoints[0].y},
				{ projectedPoints[1].x, projectedPoints[1].y},
				{ projectedPoints[2].x, projectedPoints[2].y},
			},
			meshFace.color,
			avgDepth
		};


		array_push(trianglesToRender, projectedTriangle);
	}

	int numTriangles = array_length(trianglesToRender);
	if (numTriangles > 1) {
		QuickSortTriangles(trianglesToRender, 0, numTriangles - 1);
	}

}

void Render(void) {
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);

	DrawGrid();

	int numTriangles = array_length(trianglesToRender);

	for (int i = 0; i < numTriangles; i++) {
		triangle tri = trianglesToRender[i];

		if (renderMethod & RENDER_VERTEX)
		{
			//vec2 projectedPoint = projectedPoints[i];
			DrawRectangle(tri.points[0].x, tri.points[0].y, 3, 3, 0xFFFF3333);
			DrawRectangle(tri.points[1].x, tri.points[1].y, 3, 3, 0xFFFF3333);
			DrawRectangle(tri.points[2].x, tri.points[2].y, 3, 3, 0xFFFF3333);
		}

		if (renderMethod & RENDER_TRIANGLE_FILLED)
			DrawFilledTriangle(tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, tri.color);

		if (renderMethod & RENDER_WIRE)
			DrawTriangle(tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, 0xFFFFFFFF);
	}

	array_free(trianglesToRender);

	RenderColorBuffer();
	ClearColorBuffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

void FreeResources(void) {
	free(colorBuffer);
	array_free(mesh.faces);
	array_free(mesh.vertices);
}

int main(int argc, char* args[]) {
	bIsRunning = InitializeWindow();

	Setup();

	while (bIsRunning) {
		ProcessInput();
		Update();
		Render();
	}

	DestroyWindow();
	FreeResources();
	return 0;
}