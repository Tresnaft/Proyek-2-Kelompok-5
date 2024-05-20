#ifndef LSBJPEG_H
#define LSBJPEG_H

#include "cip.h"

typedef struct {
    uint8_t *buffer;
    size_t buffer_size;
} JPEGImageData;



void open_image(const char *filename, JPEGImageData *image);
void close_image(JPEGImageData *image);
void encodeJPEG(const char *source_image, const char *dest_image, utama *var, Enkripsi *En);
void decodeJPEG(const char *image_path, char lsbjpg[]);

#endif
