// main.c

#include "bmpimgprocessing.h"

int main() {
    BMPProcessor bmpProcessor;
    initializeBMPProcessor(&bmpProcessor);

    printf("Enter BMP file path: ");
    scanf("%s", bmpProcessor.imageFilePath);

    while (!openBMPFile(&bmpProcessor, bmpProcessor.imageFilePath)) {
        printf("Enter BMP file path again: ");
        scanf("%s", bmpProcessor.imageFilePath);
    }

    printf("Enter BMP target file path: ");
    scanf("%s", bmpProcessor.targetFilePath);
    bmpProcessor.target = fopen(bmpProcessor.targetFilePath, "wb");

    // Allocate memory for pixel and byte arrays
    bmpProcessor.pic = (PIXEL *)malloc(sizeof(PIXEL) * bmpProcessor.bih.width * bmpProcessor.bih.height);
    bmpProcessor.byte = (unsigned char *)malloc(sizeof(unsigned char) * bmpProcessor.bih.width * bmpProcessor.bih.height);

    readBMPHeader(&bmpProcessor);
    readPixelData(&bmpProcessor);
    modifyLSBAndWrite(&bmpProcessor);
    closeBMPFiles(&bmpProcessor);

    // Free allocated memory
    free(bmpProcessor.pic);
    free(bmpProcessor.byte);

    return 0;
}

