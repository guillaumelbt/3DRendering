#ifndef MESH_H
#define MESH_H

#include "Vector.h"
#include "Triangle.h"

#define N_CUBE_VERTICES 8
extern vec3 cubeVertices[N_CUBE_VERTICES];

#define N_CUBE_FACES (6*2)
extern face cubeFaces[N_CUBE_FACES];

typedef struct {
	vec3* vertices;
	face* faces;
	vec3 rotation;
} mesh_t;

extern mesh_t mesh;


void LoadCubeMeshData(void);
void LoadObjFileData(char* filename);

#endif

