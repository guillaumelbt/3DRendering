#ifndef CAMERA_H
#define CAMERA_H

#include "Vector.h"

typedef struct {
    vec3 position;
    vec3 direction;
    vec3 velocity;
    float pitch;
    float roll;
    float yaw;
} Camera;

extern Camera camera;

#endif