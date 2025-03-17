#include "Display.h"
#include "Vector.h"
#include "Mesh.h"
#include "array.h"
#include "Matrix.h"
#include "Light.h"
#include "Texture.h"
#include "upng.h"
#include "Camera.h"

#define MAX_TRIANGLES 10000
triangle trianglesToRender[MAX_TRIANGLES];
int numTrianglesToRender = 0;

bool bIsRunning = false;

float previousFrameTime = 0;
float deltaTime = 0;

//triangle trianglesToRender[N_MESH_FACES];

//vec3 cameraPosition = { 0 , 0 , 0 };
mat4x4 projectionMatrix;
mat4x4 viewMatrix;
mat4x4 worldMatrix;

void Setup(void) {

	//renderMethod |= RENDER_WIRE; 
	renderMethod |= RENDER_TRIANGLE_TEXTURED;
	cullMethod = CULL_BACKFACE;

	colorBuffer = (uint32_t*)malloc(sizeof(uint32_t) * windowWidth * windowHeight);
	zBuffer = (float*)malloc(sizeof(float) * windowWidth * windowHeight);

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

	LoadObjFileData("Assets/f22.obj");
	//LoadCubeMeshData();

	LoadPngData("Assets/f22.png");

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
		case SDLK_1:
			renderMethod ^= RENDER_WIRE;
			break;
		case SDLK_2:
			renderMethod ^= RENDER_TRIANGLE_FILLED;
			if (renderMethod & RENDER_TRIANGLE_FILLED) 
			{
				renderMethod &= ~RENDER_TRIANGLE_TEXTURED;
			}
			break;
		case SDLK_3:
			renderMethod ^= RENDER_TRIANGLE_TEXTURED;
			if (renderMethod & RENDER_TRIANGLE_TEXTURED) 
			{
				renderMethod &= ~RENDER_TRIANGLE_FILLED;
			}
			break;
		case SDLK_4:
			cullMethod = !cullMethod;
			break;
		case SDLK_UP:
			camera.position.y += 3.0 * deltaTime;
			break;
		case  SDLK_DOWN:
			camera.position.y -= 3.0 * deltaTime;
			break;
		case  SDLK_q:
			camera.yaw -= 1.0 * deltaTime;
			break;
		case  SDLK_d:
			camera.yaw += 1.0 * deltaTime;
			break;
		case  SDLK_z:
			camera.velocity = Vec3Mul(camera.direction, 5.0 * deltaTime);
			camera.position = Vec3Add(camera.position, camera.velocity);
			break;
		case  SDLK_s:
			camera.velocity = Vec3Mul(camera.direction, 5.0 * deltaTime);
			camera.position = Vec3Add(camera.position, camera.velocity);
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

	deltaTime = (SDL_GetTicks() - previousFrameTime) / 1000.0;
	previousFrameTime = SDL_GetTicks();

	numTrianglesToRender = 0;

	previousFrameTime = SDL_GetTicks();

	mesh.rotation.x += 0.1 * deltaTime;
	mesh.rotation.y += 0.1 * deltaTime;
	mesh.rotation.z += 0.1 * deltaTime;
	/*mesh.scale.x += 0.002;
	mesh.scale.y += 0.002;
	mesh.scale.z += 0.002;
	mesh.translation.x += 0.01;*/
	mesh.translation.z = 5.0;

	vec3 target = { 0,0,1 };
	mat4x4 cameraYawRotation = mat4x4RotateY(camera.yaw);
	camera.direction = Vec3FromVec4(mat4x4MultVec4(cameraYawRotation, Vec4FromVec3(target)));

	mat4x4 scaleMatrix = mat4x4MakeScale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
	mat4x4 translationMatrix = mat4x4MakeTranslation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
	mat4x4 xRotationMatrix = mat4x4RotateX(mesh.rotation.x);
	mat4x4 yRotationMatrix = mat4x4RotateY(mesh.rotation.y);
	mat4x4 zRotationMatrix = mat4x4RotateZ(mesh.rotation.z);

	target = Vec3Add(camera.position, camera.direction);
	vec3 upDir = { 0,1,0 };

	viewMatrix = mat4x4LookAt(camera.position, target, upDir);

	int numFaces = array_length(mesh.faces);

	for (int i = 0; i < numFaces; i++)
	{
		face meshFace = mesh.faces[i];

		//printf_s("%d\n", mesh.faces[i].a);

		vec3 faceVertices[3];
		faceVertices[0] = mesh.vertices[meshFace.a -1];
		faceVertices[1] = mesh.vertices[meshFace.b -1];
		faceVertices[2] = mesh.vertices[meshFace.c -1];

		
		vec4 transformedVertices[3];

		for (int j = 0; j < 3; j++) {
			vec4 transformedVertex = Vec4FromVec3(faceVertices[j]);


			worldMatrix = Mat4x4Identity();

			worldMatrix = mat4x4Mult(scaleMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(zRotationMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(yRotationMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(xRotationMatrix, worldMatrix);
			worldMatrix = mat4x4Mult(translationMatrix, worldMatrix);

			transformedVertex = mat4x4MultVec4(worldMatrix, transformedVertex);

			transformedVertex = mat4x4MultVec4(viewMatrix, transformedVertex);

			//transformedVertex.z += 5;

			transformedVertices[j] = transformedVertex;
		}

		
		vec3 a = Vec3FromVec4(transformedVertices[0]);
		vec3 b = Vec3FromVec4(transformedVertices[1]);
		vec3 c = Vec3FromVec4(transformedVertices[2]);

		vec3 ab = Vec3Sub(b, a);
		vec3 ac = Vec3Sub(c, a);
		Vec3Normalize(&ab);
		Vec3Normalize(&ac);


		vec3 normal = Vec3CrossProduct(ab, ac);
		Vec3Normalize(&normal);

		vec3 origin = { 0,0,0 };
		vec3 cameraRay = Vec3Sub(a, origin);
		float dot = Vec3Dot(normal, cameraRay);

		if (cullMethod == CULL_BACKFACE)
		{
			if (dot > 0)
				continue;
		}

		vec4 projectedPoints[3];

		for (int j = 0; j < 3; j++) {
			projectedPoints[j] = mat4x4MultVec4Project(projectionMatrix,transformedVertices[j]);

			projectedPoints[j].y *= -1;

			projectedPoints[j].x *= windowWidth / 2.0;
			projectedPoints[j].y *= windowHeight / 2.0;

			projectedPoints[j].x += windowWidth / 2.0;
			projectedPoints[j].y += windowHeight / 2.0;
		}

		float avgDepth = (transformedVertices[0].z + transformedVertices[1].z + transformedVertices[2].z) / 3.0;

		float lightIntensityFactor =  -Vec3Dot(normal,mainLight.direction);

		uint32_t triangleColor = LightApplyIntensity(meshFace.color, lightIntensityFactor);

		triangle projectedTriangle =
		{
			{
				{ projectedPoints[0].x, projectedPoints[0].y, projectedPoints[0].z, projectedPoints[0].w},
				{ projectedPoints[1].x, projectedPoints[1].y, projectedPoints[1].z, projectedPoints[1].w},
				{ projectedPoints[2].x, projectedPoints[2].y, projectedPoints[2].z, projectedPoints[2].w},
			},
			{
				{meshFace.a_uv.u,meshFace.a_uv.v},
				{meshFace.b_uv.u,meshFace.b_uv.v},
				{meshFace.c_uv.u,meshFace.c_uv.v},
			},
			triangleColor,
			avgDepth
		};

		if (numTrianglesToRender < MAX_TRIANGLES)
		{
			trianglesToRender[numTrianglesToRender++] = projectedTriangle;
		}

		//array_push(trianglesToRender, projectedTriangle);
	}

	//int numTriangles = array_length(trianglesToRender);
	//if (numTriangles > 1) {
	//	QuickSortTriangles(trianglesToRender, 0, numTriangles - 1);
	//}
}

void Render(void) {
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//SDL_RenderClear(renderer);

	DrawGrid();


	for (int i = 0; i < numTrianglesToRender; i++) {
		triangle tri = trianglesToRender[i];

		if (renderMethod & RENDER_VERTEX)
		{
			DrawRectangle(tri.points[0].x, tri.points[0].y, 3, 3, 0xFFFF3333);
			DrawRectangle(tri.points[1].x, tri.points[1].y, 3, 3, 0xFFFF3333);
			DrawRectangle(tri.points[2].x, tri.points[2].y, 3, 3, 0xFFFF3333);
		}

		if (renderMethod & RENDER_TRIANGLE_FILLED)
			DrawFilledTriangle(tri.points[0].x, tri.points[0].y, tri.points[0].z, tri.points[0].w, 
				tri.points[1].x, tri.points[1].y, tri.points[1].z, tri.points[1].w, 
				tri.points[2].x, tri.points[2].y, tri.points[2].z, tri.points[2].w, 
				tri.color);

		if (renderMethod & RENDER_TRIANGLE_TEXTURED)
			DrawTexturedTriangle(
				tri.points[0].x, tri.points[0].y, tri.points[0].z, tri.points[0].w, tri.texCoords[0].u, tri.texCoords[0].v,
				tri.points[1].x, tri.points[1].y, tri.points[1].z, tri.points[1].w, tri.texCoords[1].u, tri.texCoords[1].v,
				tri.points[2].x, tri.points[2].y, tri.points[2].z, tri.points[2].w, tri.texCoords[2].u, tri.texCoords[2].v,
				meshTexture
			);

		if (renderMethod & RENDER_WIRE)
			DrawTriangle(tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, tri.color);
	}

	//array_free(trianglesToRender);

	RenderColorBuffer();
	ClearColorBuffer(0xFF000000);
	ClearZBuffer();

	SDL_RenderPresent(renderer);
}

void FreeResources(void) {
	free(colorBuffer);
	free(zBuffer);
	upng_free(pngTexture); 
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