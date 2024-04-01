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
