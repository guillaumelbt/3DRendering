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
	{.x = -1, .y = -1, .z = -1 },
	{.x = -1, .y = 1, .z = -1 }, 
	{.x = 1, .y = 1, .z = -1 }, 
	{.x = 1, .y = -1, .z = -1 }, 
	{.x = 1, .y = 1, .z = 1 }, 
	{.x = 1, .y = -1, .z = 1 }, 
	{.x = -1, .y = 1, .z = 1 }, 
	{.x = -1, .y = -1, .z = 1 }  
};

face cubeFaces[N_CUBE_FACES] = {
   {.a = 1, .b = 2, .c = 3, .a_uv = { 0, 0},.b_uv = { 0, 1},.c_uv = { 1, 1},.color = 0xFFFF0000 },
   {.a = 1, .b = 3, .c = 4, .a_uv = { 0, 0},.b_uv = { 1, 1},.c_uv = { 1, 0},.color = 0xFFFF0000 },
   {.a = 4, .b = 3, .c = 5, .a_uv = { 0, 0},.b_uv = { 0, 1},.c_uv = { 1, 1},.color = 0xFFFF0000 },
   {.a = 4, .b = 5, .c = 6, .a_uv = { 0, 0},.b_uv = { 1, 1},.c_uv = { 1, 0},.color = 0xFFFF0000 },
   {.a = 6, .b = 5, .c = 7, .a_uv = { 0, 0},.b_uv = { 0, 1},.c_uv = { 1, 1},.color = 0xFFFF0000 },
   {.a = 6, .b = 7, .c = 8, .a_uv = { 0, 0},.b_uv = { 1, 1},.c_uv = { 1, 0},.color = 0xFFFF0000 },
   {.a = 8, .b = 7, .c = 2, .a_uv = { 0, 0},.b_uv = { 0, 1},.c_uv = { 1, 1},.color = 0xFFFF0000 },
   {.a = 8, .b = 2, .c = 1, .a_uv = { 0, 0},.b_uv = { 1, 1},.c_uv = { 1, 0},.color = 0xFFFF0000 },
   {.a = 2, .b = 7, .c = 5, .a_uv = { 0, 0},.b_uv = { 0, 1},.c_uv = { 1, 1},.color = 0xFFFF0000 },
   {.a = 2, .b = 5, .c = 3, .a_uv = { 0, 0},.b_uv = { 1, 1},.c_uv = { 1, 0},.color = 0xFFFF0000 },
   {.a = 6, .b = 8, .c = 1, .a_uv = { 0, 0},.b_uv = { 0, 1},.c_uv = { 1, 1},.color = 0xFFFF0000 },
   {.a = 6, .b = 1, .c = 4, .a_uv = { 0, 0},.b_uv = { 1, 1},.c_uv = { 1, 0},.color = 0xFFFF0000 }
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

	tex2* texCoords = NULL;

	char line[256];
	while (fgets(line, sizeof(line), file))
	{
		if (!strncmp(line, "v ", 2)) {
			vec3 vertex;
			sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			array_push(mesh.vertices, vertex);
		}
		if (!strncmp(line,"vt ",3)) {
			tex2 texCoord;
			sscanf_s(line, "vt %f %f", &texCoord.u , &texCoord.v);
			array_push(texCoords, texCoord);
		}

		if (!strncmp(line, "f ", 2)) {
			int vertex_indices[3];
			int texture_indices[3];
			int normal_indices[3];
			sscanf_s(
				line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertex_indices[0], &texture_indices[0], &normal_indices[0],
				&vertex_indices[1], &texture_indices[1], &normal_indices[1],
				&vertex_indices[2], &texture_indices[2], &normal_indices[2]
			);
			face face = {
				.a = vertex_indices[0],
				.b = vertex_indices[1],
				.c = vertex_indices[2],
				.a_uv = texCoords[texture_indices[0] - 1],
				.b_uv = texCoords[texture_indices[1] - 1],
				.c_uv = texCoords[texture_indices[2] - 1],
				.color = 0xFFFFFFFF
			};
			array_push(mesh.faces, face);
		}
	}
	array_free(texCoords);
	fclose(file);	
}
