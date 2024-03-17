#ifndef PNGPROCESSOR_H
#define PNGPROCESSOR_H

typedef struct {
    unsigned char* image_data;
    int width;
    int height;
    int channels;
} Image;

Image* loadImage(const char* filename);
void hideMessage(Image* image, const char* message);
char* extractMessage(Image* image);
void saveImage(const char* filename, Image* image);
void freeImage(Image* image);

#endif /* LSB_STEGANOGRAPHY_H */

