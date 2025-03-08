#include "Mesh.h"
#include "array.h"
#include <stdio.h>
#include <string.h>

mesh_t mesh = {
	.vertices = NULL,
	.faces = NULL,
	.rotation = {0,0,0},
	.scale = { 1.0 ,1.0 ,1.0},
	.translation = { 0,0,0}
};

vec3 cubeVertices[N_CUBE_VERTICES] = {
	{.x = -1, .y = -1, .z = -1 }, // 1
	{.x = -1, .y = 1, .z = -1 }, // 2
	{.x = 1, .y = 1, .z = -1 }, // 3
	{.x = 1, .y = -1, .z = -1 }, // 4
	{.x = 1, .y = 1, .z = 1 }, // 5
	{.x = 1, .y = -1, .z = 1 }, // 6
	{.x = -1, .y = 1, .z = 1 }, // 7
	{.x = -1, .y = -1, .z = 1 }  // 8
};

face cubeFaces[N_CUBE_FACES] = {
   {.a = 1, .b = 2, .c = 3, .color = 0xFFFF0000 },
   {.a = 1, .b = 3, .c = 4, .color = 0xFFFF0000 },
   {.a = 4, .b = 3, .c = 5, .color = 0xFF00FF00 },
   {.a = 4, .b = 5, .c = 6, .color = 0xFF00FF00 },
   {.a = 6, .b = 5, .c = 7, .color = 0xFF0000FF },
   {.a = 6, .b = 7, .c = 8, .color = 0xFF0000FF },
   {.a = 8, .b = 7, .c = 2, .color = 0xFFFFFF00 },
   {.a = 8, .b = 2, .c = 1, .color = 0xFFFFFF00 },
   {.a = 2, .b = 7, .c = 5, .color = 0xFFFF00FF },
   {.a = 2, .b = 5, .c = 3, .color = 0xFFFF00FF },
   {.a = 6, .b = 8, .c = 1, .color = 0xFF00FFFF },
   {.a = 6, .b = 1, .c = 4, .color = 0xFF00FFFF }
};

void LoadCubeMeshData(void) {
	for (int i = 0; i < N_CUBE_VERTICES; i++)
	{
		vec3 cubeVertex = cubeVertices[i];
		array_push(mesh.vertices, cubeVertex);
	}

	for (int i = 0; i < N_CUBE_FACES; i++) {
		face cubeFace = cubeFaces[i];
		array_push(mesh.faces, cubeFace);
	}
}

void LoadObjFileData(char* filename) {

	FILE* file;
	fopen_s(&file, filename, "r");

	if (file == NULL) {
		printf("cannot open file\n");
		return -1;
	}

	char line[256];
	while (fgets(line, sizeof(line), file))
	{
		if (line[0] == 'v') {
			float x, y, z;
			int scanCount = sscanf_s(line, "v %f %f %f ", &x, &y, &z);
			if (scanCount == 3) {
				vec3 vertex;
				vertex.x = x; vertex.y = y; vertex.z = z;
				array_push(mesh.vertices, vertex);
			}
		}
		if (line[0] == 'f') {
			int a, b, c;
			int scanCount = sscanf_s(line, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &a, &b, &c);
			if (scanCount == 3) {
				face face;
				face.a = a; 
				face.b = b; 
				face.c = c;
				array_push(mesh.faces, face);
			}
		}
	}

	fclose(file);	
}
