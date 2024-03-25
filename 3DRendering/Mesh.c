#include "Mesh.h"


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
		vec3 cubeVertex = cubeVertices
		array_push(mesh.vertices,)
	}
}
