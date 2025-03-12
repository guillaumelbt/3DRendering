#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "upng.h"

typedef struct
{
	float u;
	float v;
} tex2;

extern int texWidth;
extern int texHeight;

extern uint32_t* meshTexture;
extern upng_t* pngTexture;

void LoadPngData(char* filename);

#endif