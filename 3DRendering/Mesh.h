#ifndef MESH_H
#define MESH_H

#include "Vector.h"
#include "Triangle.h"

#define N_MESH_VERTICES 8
extern vec3 meshVertices[N_MESH_VERTICES];

#define N_MESH_FACES (6*2)
extern face meshFaces[N_MESH_FACES];

#endif

