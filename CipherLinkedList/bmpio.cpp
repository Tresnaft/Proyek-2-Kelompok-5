#include "bmpio.h"

BMPImage *readBMP(const char *filename, BMPHeader *header) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

//    fread(header, sizeof(header), 1, file);
	fread(&(header->signature), sizeof(header->signature), 1, file);
    fread(&(header->fileSize), sizeof(header->fileSize), 1, file);
    fread(&(header->reserved1), sizeof(header->reserved1), 1, file);
    fread(&(header->reserved2), sizeof(header->reserved2), 1, file);
    fread(&(header->dataOffset), sizeof(header->dataOffset), 1, file);
    fread(&(header->headerSize), sizeof(header->headerSize), 1, file);
    fread(&(header->width), sizeof(header->width), 1, file);
    fread(&(header->height), sizeof(header->height), 1, file);
    fread(&(header->planes), sizeof(header->planes), 1, file);
    fread(&(header->bitsPerPixel), sizeof(header->bitsPerPixel), 1, file);
    fread(&(header->compression), sizeof(header->compression), 1, file);
    fread(&(header->dataSize), sizeof(header->dataSize), 1, file);
    fread(&(header->hResolution), sizeof(header->hResolution), 1, file);
    fread(&(header->vResolution), sizeof(header->vResolution), 1, file);
    fread(&(header->colors), sizeof(header->colors), 1, file);
    fread(&(header->importantColors), sizeof(header->importantColors), 1, file);

    if (header->signature != 0x4D42) {
        fprintf(stderr, "Invalid BMP file format\n");
        fclose(file);
        exit(1);
    }

    if (header->bitsPerPixel != 24) {
        fprintf(stderr, "Unsupported bits per pixel\n");
        fclose(file);
        exit(1);
    }

    BMPImage *img = (BMPImage *)malloc(sizeof(BMPImage));
    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        fclose(file);
        exit(1);
    }

    img->width = header->width;
    img->height = header->height;

    fseek(file, header->dataOffset, SEEK_SET);

    img->data = (RGBPixel *)malloc(sizeof(RGBPixel) * img->width * img->height);
    if (!img->data) {
        fprintf(stderr, "Unable to allocate memory\n");
        fclose(file);
        free(img);
        exit(1);
    }

    int padding = (4 - (img->width * sizeof(RGBPixel)) % 4) % 4;
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            fread(&img->data[y * img->width + x], sizeof(RGBPixel), 1, file);
        }
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return img;
}

void writeBMP(const char *filename, BMPImage *img, BMPHeader header) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

//    BMPHeader header = {0};
    header.signature = 0x4D42; // BM
    header.fileSize = sizeof(BMPHeader) + (img->width * sizeof(RGBPixel) + ((4 - (img->width * sizeof(RGBPixel)) % 4) % 4)) * img->height;
    header.dataOffset = sizeof(BMPHeader);
    header.headerSize = 40;
    header.width = img->width;
    header.height = img->height;
    header.planes = 1;
    header.bitsPerPixel = 24;
    header.compression = 0;
    header.dataSize = (img->width * sizeof(RGBPixel) + ((4 - (img->width * sizeof(RGBPixel)) % 4) % 4)) * img->height;
    header.hResolution = 0;
    header.vResolution = 0;
    header.colors = 0;
    header.importantColors = 0;
    
    
//	printf("Signature: 0x%X\n", header.signature);
//	printf("File Size: %u bytes\n", header.fileSize);
//	printf("Reserved 1: %u\n", header.reserved1);
//	printf("Reserved 2: %u\n", header.reserved2);
//	printf("Data Offset: %u bytes\n", header.dataOffset);
//	printf("Header Size: %u bytes\n", header.headerSize);
//	printf("Width: %d pixels\n", header.width);
//	printf("Height: %d pixels\n", header.height);
//	printf("Planes: %u\n", header.planes);
//	printf("Bits per Pixel: %u\n", header.bitsPerPixel);
//	printf("Compression: %u\n", header.compression);
//	printf("Data Size: %u bytes\n", header.dataSize);
//	printf("Horizontal Resolution: %d pixels per meter\n", header.hResolution);
//	printf("Vertical Resolution: %d pixels per meter\n", header.vResolution);
//	printf("Colors: %u\n", header.colors);
//	printf("Important Colors: %u\n", header.importantColors);
    fwrite(&header, sizeof(header), 1, file);

    int padding = (4 - (img->width * sizeof(RGBPixel)) % 4) % 4; // Padding bytes per row
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            fwrite(&img->data[y * img->width + x], sizeof(RGBPixel), 1, file);
        }
        // Write padding bytes
        for (int p = 0; p < padding; p++) {
            fputc(0, file);
        }
    }

    fclose(file);
}
