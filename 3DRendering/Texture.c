#include "Texture.h"

int texWidth = 64;
int texHeight = 64;
uint32_t* meshTexture = NULL;
upng_t* pngTexture = NULL;

void LoadPngData(char* filename) {
    pngTexture = upng_new_from_file(filename);
    if (pngTexture != NULL) {
        upng_decode(pngTexture);
        if (upng_get_error(pngTexture) == UPNG_EOK) {
            meshTexture = (uint32_t*)upng_get_buffer(pngTexture);
            texWidth = upng_get_width(pngTexture);
            texHeight = upng_get_height(pngTexture);
        }
    }
}

