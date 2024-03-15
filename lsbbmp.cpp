#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <string.h>
#include "lsbbmp.h"

#define MAX_MESSAGE_LENGTH 2048

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

void inputMessage(char *message) {
    int messageLength;
    char pesan[MAX_MESSAGE_LENGTH];
    char str[MAX_MESSAGE_LENGTH]; // Perbaiki deklarasi str sebagai array karakter
    int i;
    
    printf("Masukkan pesan yang ingin disembunyikan: ");
    fgets(pesan, MAX_MESSAGE_LENGTH, stdin);

    // Menghapus karakter newline jika ada
    if ((strlen(pesan) > 0) && (pesan[strlen(pesan) - 1] == '\n')) {
        pesan[strlen(pesan) - 1] = '\0';
    }

    // Menghitung jumlah byte dalam pesan
    messageLength = strlen(pesan) + 1; // Jumlah byte termasuk karakter null terminator
    
    sprintf(str, "%d", messageLength); // Menyimpan messageLength sebagai karakter ke dalam str
    printf("%s\n", str); // Cetak str sebagai string, bukan sebagai satu karakter

    // Menyalin pesan ke array message dimulai dari indeks ke-1
    message[0] = str[0];
    message[1] = str[1];
    message[2] = str[2];
    
    if (message[1] == 0) {
    	message[1] = 48;
	}
	if (message[2] == 0) {
    	message[2] = 48;
	}
    
    printf("message 0 : %d\n", message[0]);
    printf("message 1 : %d\n", message[1]);
    printf("message 2 : %d\n", message[2]);
    
    for (i = 3; i < messageLength + 3; i++) {
        message[i] = pesan[i - 3];
        
    }
    for (i = 0; i < messageLength + 3; i++) {
    	printf("%c", message[i]);
	}
}

char* messageToBinary(char* s) {
    if (s == NULL) return NULL; // Handle NULL input

    size_t len = strlen(s);
    
    char *binary = (char *)malloc(len * 8 + 1); // Allocate memory for binary string
    if (binary == NULL) return NULL; // Check for allocation failure
    binary[0] = '\0';
    for (size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for (int j = 7; j >= 0; --j) {
            if (ch & (1 << j)) {
                strcat(binary, "1");
            } else {
                strcat(binary, "0");
            }
        }
    }
    return binary;
}

void writeMsg(BMPImage *img, const char *binaryMessage) {
    int len = strlen(binaryMessage);
    int bitIndex = 0;
    for (int i = 0; i < img->width * img->height; i++) {
 	for (int bit = 0; bit < 2; bit++) {
            if (bitIndex < len) {
                unsigned char *color;
                switch (bit) {
                    case 0: color = &img->data[i].red; break;
                    case 1: color = &img->data[i].blue; break;
                }
                *color = (*color & 0xFE) | (binaryMessage[bitIndex++] - '0');
	    	}
		}
	}
}

void writeBMP(const char *filename, BMPImage *img) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    BMPHeader header = {0};
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


int extractinfolen(const BMPImage *img) {
	unsigned char combinedValue1 = 0;
	unsigned char combinedValue2 = 0;
	unsigned char combinedValue3 = 0;
	char arraypanjang[3];
	int combinedValue;
	int j = 0;
    if (!img) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    
    
	unsigned char lsbsem1[8], lsbsem2[8], lsbsem3[8];
	
    for (int i = 0; i < 1; i+=4) {
    	
		
        unsigned char redLSB = img->data[i].red & 1;
        unsigned char blueLSB = img->data[i].blue & 1;
        unsigned char redLSB2 = img->data[i+1].red & 1;
        unsigned char blueLSB2 = img->data[i+1].blue & 1;
        unsigned char redLSB3 = img->data[i+2].red & 1;
        unsigned char blueLSB3 = img->data[i+2].blue & 1;
        unsigned char redLSB4 = img->data[i+3].red & 1;
		unsigned char blueLSB4 = img->data[i+3].blue & 1;
		
		lsbsem1[0] = redLSB;
		lsbsem1[1] = blueLSB;
		lsbsem1[2] = redLSB2;
		lsbsem1[3] = blueLSB2;
		lsbsem1[4] = redLSB3;
		lsbsem1[5] = blueLSB3;
		lsbsem1[6] = redLSB4;
		lsbsem1[7] = blueLSB4;
		

		
        unsigned char redLSB5 = img->data[i+4].red & 1;
        unsigned char blueLSB5 = img->data[i+4].blue & 1;
        unsigned char redLSB6 = img->data[i+5].red & 1;
        unsigned char blueLSB6 = img->data[i+5].blue & 1;
        unsigned char redLSB7 = img->data[i+6].red & 1;
        unsigned char blueLSB7 = img->data[i+6].blue & 1;
        unsigned char redLSB8 = img->data[i+7].red & 1;
		unsigned char blueLSB8 = img->data[i+7].blue & 1;
		
		lsbsem2[0] = redLSB5;
		lsbsem2[1] = blueLSB5;
		lsbsem2[2] = redLSB6;
		lsbsem2[3] = blueLSB6;
		lsbsem2[4] = redLSB7;
		lsbsem2[5] = blueLSB7;
		lsbsem2[6] = redLSB8;
		lsbsem2[7] = blueLSB8;
	
	    unsigned char redLSB9 = img->data[i+8].red & 1;
        unsigned char blueLSB9 = img->data[i+8].blue & 1;
        unsigned char redLSB10 = img->data[i+9].red & 1;
        unsigned char blueLSB10 = img->data[i+9].blue & 1;
        unsigned char redLSB11 = img->data[i+10].red & 1;
        unsigned char blueLSB11 = img->data[i+10].blue & 1;
        unsigned char redLSB12 = img->data[i+11].red & 1;
		unsigned char blueLSB12 = img->data[i+11].blue & 1;
		
		lsbsem3[0] = redLSB9;
		lsbsem3[1] = blueLSB9;
		lsbsem3[2] = redLSB10;
		lsbsem3[3] = blueLSB10;
		lsbsem3[4] = redLSB11;
		lsbsem3[5] = blueLSB11;
		lsbsem3[6] = redLSB12;
		lsbsem3[7] = blueLSB12;
		

		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}
		
	

		for (int q = 0; q < 8; q++) {
		    combinedValue2 |= lsbsem2[q] << (7 - q);
		}
    
        for (int q = 0; q < 8; q++) {
		    combinedValue3 |= lsbsem3[q] << (7 - q);
		}
		combinedValue1 = combinedValue1 - '0';
		combinedValue2 = combinedValue2 - '0';
		combinedValue3 = combinedValue3 - '0';
		
		if (combinedValue1 != 0 && combinedValue2 != 0 && combinedValue3 != 0) {
			combinedValue = combinedValue1 * 100 + combinedValue2 * 10 + combinedValue3;
		}
		if (combinedValue2 == 0 && combinedValue3 == 0) {
			combinedValue = combinedValue1;
		}
		if (combinedValue1 != 0 && combinedValue2 != 0 && combinedValue3 == 0) {
			combinedValue =  combinedValue1 * 10 + combinedValue2;
		}

        memset(lsbsem1, 0, sizeof(lsbsem1));
        memset(lsbsem2, 0, sizeof(lsbsem2));
        memset(lsbsem3, 0, sizeof(lsbsem3));
		
    }
    return(combinedValue);
}


void extractlsbinfolen(const BMPImage *img, int len, int panjang) {
	char* dekripsi = (char* ) malloc (panjang * sizeof(char));
	char tes;

    if (!img) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    char combinedValue[panjang]; 

    int index = 0;
    

    
	unsigned char lsbsem1[8], lsbsem2[8], lsbsem3[8];
	
    for (int i = 12; i < len; i+=4) {
    	unsigned char combinedValue1 = 0;
		unsigned char combinedValue2 = 0;
		unsigned char combinedValue3 = 0;
		
        unsigned char redLSB = img->data[i].red & 1;
        unsigned char blueLSB = img->data[i].blue & 1;
        
        unsigned char redLSB2 = img->data[i+1].red & 1;
        unsigned char blueLSB2 = img->data[i+1].blue & 1;
        
        unsigned char redLSB3 = img->data[i+2].red & 1;
        unsigned char blueLSB3 = img->data[i+2].blue & 1;
        
        unsigned char redLSB4 = img->data[i+3].red & 1;
		unsigned char blueLSB4 = img->data[i+3].blue & 1;
		
		lsbsem1[0] = redLSB;
		lsbsem1[1] = blueLSB;
		lsbsem1[2] = redLSB2;
		lsbsem1[3] = blueLSB2;
		lsbsem1[4] = redLSB3;
		lsbsem1[5] = blueLSB3;
		lsbsem1[6] = redLSB4;
		lsbsem1[7] = blueLSB4;
		

		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}
		
		combinedValue[index++] = combinedValue1;
		
		// printf("%c", combinedValue1);
   	}
   	
   	
		for (int i = 0; i < panjang - 1; i++) {
        printf("%c", combinedValue[i]);
		}
}