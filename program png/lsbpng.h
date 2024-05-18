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
} PNGImageData;

PNGImageData *loadImage(char *filename);
void freeImageData(PNGImageData *img_data);
void encodePNG(char *src_image, char *dest_image, char *message);
void decodePNG(char *src_image);

#endif

