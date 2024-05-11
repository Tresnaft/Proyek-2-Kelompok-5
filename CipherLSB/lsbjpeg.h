#ifndef LSBJPEG_H
#define LSBJPEG_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lsbbmp.h"
#include "cip.h"

typedef struct {
    uint8_t *buffer;
    size_t buffer_size;
} ImageData;



void open_image(const char *filename, ImageData *image);
void close_image(ImageData *image);
void encode(const char *source_image, const char *dest_image, utama *var, Enkripsi *En);
void decode(const char *image_path, char lsbjpg[]);

#endif
