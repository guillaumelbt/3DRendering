#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	float u;
	float v;
} tex2;

extern int texWidth;
extern int texHeight;

extern const uint8_t REDBRICK_TEXTURE[];
extern uint32_t* meshTexture;


#endif