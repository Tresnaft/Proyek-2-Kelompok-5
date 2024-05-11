#ifndef LSB_IMAGE_H
#define LSB_IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "tambahan untuk png.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tambahan untuk png-wtite.h"

typedef struct {
    unsigned char *image;
    int width;
    int height;
    int channels;
} ImageData;

ImageData *loadImage(char *filename);
void freeImageData(ImageData *img_data);
void encode(char *src_image, char *dest_image, char *message);
void decode(char *src_image);

#endif
