#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <string.h>

typedef struct {
    unsigned char red, green, blue;
} RGBPixel;

typedef struct {
    int width, height;
    RGBPixel *data;
} BMPImage;

#pragma pack(push, 1)
typedef struct {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t dataSize;
    int32_t hResolution;
    int32_t vResolution;
    uint32_t colors;
    uint32_t importantColors;
} BMPHeader;
#pragma pack(pop)

BMPImage *readBMP(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    BMPHeader header;
    fread(&header, sizeof(header), 1, file);

    if (header.signature != 0x4D42) {
        fprintf(stderr, "Invalid BMP file format\n");
        fclose(file);
        exit(1);
    }

    if (header.bitsPerPixel != 24) {
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

    img->width = header.width;
    img->height = header.height;

    fseek(file, header.dataOffset, SEEK_SET);

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


void extractLSB(const BMPImage *img) {
    if (!img) {
        fprintf(stderr, "Invalid input\n");
        return;
    }
	unsigned char lsbsem1[8], lsbsem2[8], lsbsem3[8];

    int dataIndex = 0;
    for (int i = 0; i < 100; i += 8) {
    	unsigned char combinedValue1 = 0;
		unsigned char combinedValue2 = 0;
		unsigned char combinedValue3 = 0;
		
        unsigned char redLSB = img->data[i].red & 1;
        unsigned char greenLSB = img->data[i].green & 1;
        unsigned char blueLSB = img->data[i].blue & 1;
        
        unsigned char redLSB2 = img->data[i+1].red & 1;
        unsigned char greenLSB2 = img->data[i+1].green & 1;
        unsigned char blueLSB2 = img->data[i+1].blue & 1;
        
        unsigned char redLSB3 = img->data[i+2].red & 1;
        unsigned char greenLSB3 = img->data[i+2].green & 1;
        lsbsem1[0] = redLSB;
		lsbsem1[1] = greenLSB;
		lsbsem1[2] = blueLSB;
		lsbsem1[3] = redLSB2;
		lsbsem1[4] = greenLSB2;
		lsbsem1[5] = blueLSB2;
		lsbsem1[6] = redLSB3;
		lsbsem1[7] = greenLSB3;
		

		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}

		
		
		


        
        unsigned char blueLSB3 = img->data[i+2].blue & 1;
        
        unsigned char redLSB4 = img->data[i+3].red & 1;
        unsigned char greenLSB4 = img->data[i+3].green & 1;
        unsigned char blueLSB4 = img->data[i+3].blue & 1;
        
        unsigned char redLSB5 = img->data[i+4].red & 1;
        unsigned char greenLSB5 = img->data[i+4].green & 1;
        unsigned char blueLSB5 = img->data[i+4].blue & 1;
        
        unsigned char redLSB6 = img->data[i+5].red & 1;
        
        lsbsem2[0] = blueLSB3;
		lsbsem2[1] = redLSB4;
		lsbsem2[2] = greenLSB4;
		lsbsem2[3] = blueLSB4;
		lsbsem2[4] = redLSB5;
		lsbsem2[5] = greenLSB5;
		lsbsem2[6] = blueLSB5;
		lsbsem2[7] = redLSB6;

		
		for (int q = 0; q < 8; q++) {
		    combinedValue2 |= lsbsem2[q] << (7 - q);
		}
	
        
        
        
        unsigned char greenLSB6 = img->data[i+5].green & 1;
        unsigned char blueLSB6 = img->data[i+5].blue & 1;
        
        unsigned char redLSB7 = img->data[i+6].red & 1;
        unsigned char greenLSB7 = img->data[i+6].green & 1;
        unsigned char blueLSB7 = img->data[i+6].blue & 1;
        
        unsigned char redLSB8 = img->data[i+7].red & 1;
        unsigned char greenLSB8 = img->data[i+7].green & 1;
        unsigned char blueLSB8 = img->data[i+7].blue & 1;
        
        lsbsem3[0] = greenLSB6;
		lsbsem3[1] = blueLSB6;
		lsbsem3[2] = redLSB7;
		lsbsem3[3] = greenLSB7;
		lsbsem3[4] = blueLSB7;
		lsbsem3[5] = redLSB8;
		lsbsem3[6] = greenLSB8;
		lsbsem3[7] = blueLSB8;
		

        
        for (int q = 0; q < 8; q++) {
		    combinedValue3 |= lsbsem3[q] << (7 - q);
		}

	
		printf("%c", combinedValue1);
		printf("%c", combinedValue2);
		printf("%c", combinedValue3);
		
		
        memset(lsbsem1, 0, sizeof(lsbsem1));
        memset(lsbsem2, 0, sizeof(lsbsem2));
        memset(lsbsem3, 0, sizeof(lsbsem3));
        
        
        

		
    }
}






int main() {
    BMPImage *image;
    const char *filename_read = "sampleout.bmp";
    printf("%s\n", filename_read);
    // Membaca gambar BMP dari file
    image = readBMP(filename_read);

    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    // Mengambil bit terakhir dari setiap byte dalam komponen warna
    int dataSize = image->width * image->height;
    extractLSB(image);

    // Membebaskan memori yang digunakan oleh gambar dan data bit terakhir
    free(image->data);
    free(image);

    return 0;
}