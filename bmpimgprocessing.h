

#ifndef bmpimgprocessing_H
#define bmpimgprocessing_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned int size;
	unsigned int width;
	unsigned int height;
}BITMAPINFOHEADER;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} PIXEL;

typedef struct {
    FILE *image;
    FILE *target;
    char imageFilePath[1000];
    char targetFilePath[1000];
    BITMAPINFOHEADER bih;
    PIXEL *pic;
    unsigned char *byte;
} BMPProcessor;

void initializeBMPProcessor(BMPProcessor *bmpProcessor);
int openBMPFile(BMPProcessor *bmpProcessor, const char *filePath);
void readBMPHeader(BMPProcessor *bmpProcessor);
void readPixelData(BMPProcessor *bmpProcessor);
void modifyLSBAndWrite(BMPProcessor *bmpProcessor);
void closeBMPFiles(BMPProcessor *bmpProcessor);
int get_LSB(unsigned char byte);
void WriteTargetFile(BMPProcessor *bmpProcessor);
#endif 

