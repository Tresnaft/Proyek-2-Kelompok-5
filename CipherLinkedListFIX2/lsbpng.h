#ifndef LSBPNG_H
#define LSBPNG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    unsigned char *image;
    int width;
    int height;
    int channels;
} PNGImageData;

PNGImageData *loadImage(char *filename);
void freeImageData(PNGImageData *img_data);
void encodePNG(char *src_image, char *dest_image, char *message);
void decodePNG(char *src_image, char *message);

#endif

