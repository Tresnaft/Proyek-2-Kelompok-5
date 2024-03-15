#include "bmpimgprocessing.h"

// Function to initialize the BMPProcessor
void initializeBMPProcessor(BMPProcessor *bmpProcessor) {
    bmpProcessor->image = NULL;
    bmpProcessor->target = NULL;
    bmpProcessor->pic = NULL;
    bmpProcessor->byte = NULL;
}

// Function to open the BMP file
int openBMPFile(BMPProcessor *bmpProcessor, const char *filePath) {
    bmpProcessor->image = fopen(filePath, "rb");
    if (bmpProcessor->image == NULL) {
        printf("Error! Unable to open file: %s\n", filePath);
        return 0;
    }
    return 1;
}

// Function to read BMP header information
void readBMPHeader(BMPProcessor *bmpProcessor) {
    fseek(bmpProcessor->image, 2, SEEK_SET);
    fread(&bmpProcessor->bih.size, 4, 1, bmpProcessor->image);

    fseek(bmpProcessor->image, 18, SEEK_SET);
    fread(&bmpProcessor->bih.width, 4, 1, bmpProcessor->image);
    fseek(bmpProcessor->image, 22, SEEK_SET);
    fread(&bmpProcessor->bih.height, 4, 1, bmpProcessor->image);
}

// Function to read pixel data from the BMP file
void readPixelData(BMPProcessor *bmpProcessor) {
    int i = 0;
    while (fread(&bmpProcessor->pic[i], sizeof(PIXEL), 1, bmpProcessor->image) == 1) {
        i++;
    }
}

void WriteTargetFile(BMPProcessor *bmpProcessor){
	rewind(bmpProcessor->image);
	while (fread(bmpProcessor->byte, sizeof(unsigned char), 1, bmpProcessor->image)==1){
//		byte[i] = (*byte & 0xFE) | (i & 0x01);
		fwrite(bmpProcessor->byte, sizeof(unsigned char), 1, bmpProcessor->target);
	}
}

// Function to close BMP files
void closeBMPFiles(BMPProcessor *bmpProcessor) {
    fclose(bmpProcessor->target);
    fclose(bmpProcessor->image);
}

int get_LSB(unsigned char byte){
	return byte & 0x01;
}
