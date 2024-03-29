#include "Mesh.h"
#include "array.h"
#include <stdio.h>
#include <string.h>

mesh_t mesh = {
	.vertices = NULL,
	.faces = NULL,
	.rotation = {0,0,0}
};

vec3 cubeVertices[N_CUBE_VERTICES] = {
	{ -1, -1 , -1 },	//1
	{ -1,  1 , -1 },	//2
	{  1,  1 , -1 },	//3
	{  1, -1 , -1 },	//4
	{  1,  1 ,  1 },	//5
	{  1, -1 ,  1 },	//6
	{ -1,  1 ,  1 },	//7
	{ -1, -1 ,  1 }		//8
};

face cubeFaces[N_CUBE_FACES] = {
	{ 1 , 2 , 3 },
	{ 1 , 3 , 4 },


	{ 4 , 3 , 5 },
	{ 4 , 5 , 6 },

	{ 6 , 5 , 7 },
	{ 6 , 7 , 8 },

	{ 8 , 7 , 2 },
	{ 8 , 2 , 1 },

	{ 2 , 7 , 2 },
	{ 2 , 5 , 1 },

	{ 6 , 8 , 1 },
	{ 6 , 1 , 4 },
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

	mesh.vertices = NULL;
	mesh.faces = NULL;
	mesh.rotation.x = 0;
	mesh.rotation.y = 0;
	mesh.rotation.z = 0;

	FILE* file;
	fopen_s(&file, filename, "r");

	char line[1024];

	while (fgets(line, 1024, file)) {
		//printf_s("%d\n", strncmp(line, "v", 2));
		if (strncmp(line, "v", 2) == 1) {
			
			vec3 vertex;
			sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			printf_s("%f\n", vertex.x);
			printf_s("%f\n", vertex.y);
			printf_s("%f\n", vertex.z);
			array_push(mesh.vertices, vertex);
		}
		if (strncmp(line, "f", 2) == 1) {

			int vertexIndices[3];
			int textureIndices[3];
			int normalIndices[3];
			sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", 
				&vertexIndices[0], &textureIndices[0], &normalIndices[0],
				&vertexIndices[1], &textureIndices[1], &normalIndices[1], 
				&vertexIndices[2], &textureIndices[2], &normalIndices[2]
			);
			face f = {
				.a = vertexIndices[0],
				.b = vertexIndices[1],
				.c = vertexIndices[2]
			};
			//printf_s("%d\n", f.a);
			//printf_s("%d\n", f.b);
			//printf_s("%d\n", f.c);
			array_push(mesh.faces, f);
		}
		//printf_s("%d\n", mesh.faces[0].a);
	}
	//printf_s("%d\n",array_length(mesh.vertices));
	//printf_s("%d\n", array_length(mesh.faces));
}
