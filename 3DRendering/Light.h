#ifndef LIGHT_H
#define LIGHT_H

#include "Vector.h"
#include <stdio.h>
#include <stdint.h>

typedef struct
{
	vec3 direction;
} light;

extern light mainLight;

uint32_t LightApplyIntensity(uint32_t color, float factor);
#endif
