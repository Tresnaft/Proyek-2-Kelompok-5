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
//        unsigned char greenLSB = img->data[i].green & 1;
        unsigned char blueLSB = img->data[i].blue & 1;
        
        unsigned char redLSB2 = img->data[i+1].red & 1;
//        unsigned char greenLSB2 = img->data[i+1].green & 1;
        unsigned char blueLSB2 = img->data[i+1].blue & 1;
        
        unsigned char redLSB3 = img->data[i+2].red & 1;
//        unsigned char greenLSB3 = img->data[i+2].green & 1;
        unsigned char blueLSB3 = img->data[i+2].blue & 1;
        
        unsigned char redLSB4 = img->data[i+3].red & 1;
//        unsigned char greenLSB4 = img->data[i+3].green & 1;
		unsigned char blueLSB4 = img->data[i+3].blue & 1;
		
		lsbsem1[0] = redLSB;
		lsbsem1[1] = blueLSB;
		lsbsem1[2] = redLSB2;
		lsbsem1[3] = blueLSB2;
		lsbsem1[4] = redLSB3;
		lsbsem1[5] = blueLSB3;
		lsbsem1[6] = redLSB4;
		lsbsem1[7] = blueLSB4;
		

		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}
		
        unsigned char redLSB5 = img->data[i+4].red & 1;
//        unsigned char greenLSB = img->data[i].green & 1;
        unsigned char blueLSB5 = img->data[i+4].blue & 1;
        
        unsigned char redLSB6 = img->data[i+5].red & 1;
//        unsigned char greenLSB2 = img->data[i+1].green & 1;
        unsigned char blueLSB6 = img->data[i+5].blue & 1;
        
        unsigned char redLSB7 = img->data[i+6].red & 1;
//        unsigned char greenLSB3 = img->data[i+2].green & 1;
        unsigned char blueLSB7 = img->data[i+6].blue & 1;
        
        unsigned char redLSB8 = img->data[i+7].red & 1;
//        unsigned char greenLSB4 = img->data[i+3].green & 1;
		unsigned char blueLSB8 = img->data[i+7].blue & 1;
		
		lsbsem2[0] = redLSB5;
		lsbsem2[1] = blueLSB5;
		lsbsem2[2] = redLSB6;
		lsbsem2[3] = blueLSB6;
		lsbsem2[4] = redLSB7;
		lsbsem2[5] = blueLSB7;
		lsbsem2[6] = redLSB8;
		lsbsem2[7] = blueLSB8;
		

		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
		for (int q = 0; q < 8; q++) {
		    combinedValue2 |= lsbsem2[q] << (7 - q);
		}
	
	    unsigned char redLSB9 = img->data[i+8].red & 1;
//        unsigned char greenLSB = img->data[i].green & 1;
        unsigned char blueLSB9 = img->data[i+8].blue & 1;
        
        unsigned char redLSB10 = img->data[i+9].red & 1;
//        unsigned char greenLSB2 = img->data[i+1].green & 1;
        unsigned char blueLSB10 = img->data[i+9].blue & 1;
        
        unsigned char redLSB11 = img->data[i+10].red & 1;
//        unsigned char greenLSB3 = img->data[i+2].green & 1;
        unsigned char blueLSB11 = img->data[i+10].blue & 1;
        
        unsigned char redLSB12 = img->data[i+11].red & 1;
//        unsigned char greenLSB4 = img->data[i+3].green & 1;
		unsigned char blueLSB12 = img->data[i+11].blue & 1;
		
		lsbsem3[0] = redLSB9;
		lsbsem3[1] = blueLSB9;
		lsbsem3[2] = redLSB10;
		lsbsem3[3] = blueLSB10;
		lsbsem3[4] = redLSB11;
		lsbsem3[5] = blueLSB11;
		lsbsem3[6] = redLSB12;
		lsbsem3[7] = blueLSB12;
		

		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
		for (int q = 0; q < 8; q++) {
		    combinedValue3 |= lsbsem3[q] << (7 - q);
		}
		
	
	
// KAYANYA GAGALLLL
		
//		combinedValue1 = combinedValue1 - '0';
//		if (combinedValue1 == 0) {
//			arraypanjang[j] = 0;
//			printf("combine value [%d]: %d\n", j, combinedValue1);
//			j++;
//		} else {
//			arraypanjang[j] = combinedValue1;
//			printf("combine value [%d]: %d\n", j, combinedValue1);
//			j++;
//		}
//		if (combinedValue1 != 0 && combinedValue2 != 0 && combinedValue3 != 0) {
//			combinedValue = combinedValue1 * 100 + combinedValue2 * 10 + combinedValue3;
//		}
//		if (combinedValue2 == 0 && combinedValue3 == 0) {
//			combinedValue = combinedValue1;
//		}
//		if (combinedValue1 != 0 && combinedValue2 != 0 && combinedValue3 == 0) {
//			combinedValue =  combinedValue1 * 10 + combinedValue2;
//		}
		
		
		
		


    // KODINGAN DULUUUUUUUUUUUUUUUUUUUUUU //
        
//        unsigned char blueLSB4 = img->data[i+3].blue & 1;
//        
//        unsigned char redLSB5 = img->data[i+4].red & 1;
//        unsigned char greenLSB5 = img->data[i+4].green & 1;
//        unsigned char blueLSB5 = img->data[i+4].blue & 1;
//        
//        unsigned char redLSB6 = img->data[i+5].red & 1;
//        
//        lsbsem2[0] = blueLSB3;
//		lsbsem2[1] = redLSB4;
//		lsbsem2[2] = greenLSB4;
//		lsbsem2[3] = blueLSB4;
//		lsbsem2[4] = redLSB5;
//		lsbsem2[5] = greenLSB5;
//		lsbsem2[6] = blueLSB5;
//		lsbsem2[7] = redLSB6;
//
//		
		for (int q = 0; q < 8; q++) {
		    combinedValue2 |= lsbsem2[q] << (7 - q);
		}
//	
//        
//        
//        
//        unsigned char greenLSB6 = img->data[i+5].green & 1;
//        unsigned char blueLSB6 = img->data[i+5].blue & 1;
//        
//        unsigned char redLSB7 = img->data[i+6].red & 1;
//        unsigned char greenLSB7 = img->data[i+6].green & 1;
//        unsigned char blueLSB7 = img->data[i+6].blue & 1;
//        
//        unsigned char redLSB8 = img->data[i+7].red & 1;
//        unsigned char greenLSB8 = img->data[i+7].green & 1;
//        unsigned char blueLSB8 = img->data[i+7].blue & 1;
//        
//      lsbsem3[0] = greenLSB6;
//		lsbsem3[1] = blueLSB6;
//		lsbsem3[2] = redLSB7;
//		lsbsem3[3] = greenLSB7;
//		lsbsem3[4] = blueLSB7;
//		lsbsem3[5] = redLSB8;
//		lsbsem3[6] = greenLSB8;
//		lsbsem3[7] = blueLSB8;
//		
//
//        
        for (int q = 0; q < 8; q++) {
		    combinedValue3 |= lsbsem3[q] << (7 - q);
		}
//		printf("combine value 1 sebelum %d\n", combinedValue1);
//		printf("combine value 2 sebelum %d\n", combinedValue2);
//		printf("combine value 3 sebelum %d\n", combinedValue3);
		
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

		
		
		
//		printf("combine value : %d\n", combinedValue);
		
//		printf("combine value 1 : %d\n", combinedValue1);
//		printf("combine value 2 : %d\n", combinedValue2);
//		printf("combine value 3 : %d\n", combinedValue3);
//		
//		printf("%c", combinedValue1);
//		printf("%c", combinedValue2);
//		printf("%c", combinedValue3);

		
		
        memset(lsbsem1, 0, sizeof(lsbsem1));
        memset(lsbsem2, 0, sizeof(lsbsem2));
        memset(lsbsem3, 0, sizeof(lsbsem3));
        
        
        

		
    }
    return(combinedValue);
}

// algoritma infolen
void extractlsbinfolen(const BMPImage *img, int len) {
    if (!img) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    
    
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
		

		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}
		
//        unsigned char redLSB5 = img->data[i+4].red & 1;
//        unsigned char blueLSB5 = img->data[i+4].blue & 1;
//        
//        unsigned char redLSB6 = img->data[i+5].red & 1;
//        unsigned char blueLSB6 = img->data[i+5].blue & 1;
//        
//        unsigned char redLSB7 = img->data[i+6].red & 1;
//        unsigned char blueLSB7 = img->data[i+6].blue & 1;
//        
//        unsigned char redLSB8 = img->data[i+7].red & 1;
//		unsigned char blueLSB8 = img->data[i+7].blue & 1;
//		
//		lsbsem2[0] = redLSB5;
//		lsbsem2[1] = blueLSB5;
//		lsbsem2[2] = redLSB6;
//		lsbsem2[3] = blueLSB6;
//		lsbsem2[4] = redLSB7;
//		lsbsem2[5] = blueLSB7;
//		lsbsem2[6] = redLSB8;
//		lsbsem2[7] = blueLSB8;
//		
//
//		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
//		for (int q = 0; q < 8; q++) {
//		    combinedValue2 |= lsbsem2[q] << (7 - q);
//		}
//	
//	    unsigned char redLSB9 = img->data[i+8].red & 1;
//        unsigned char blueLSB9 = img->data[i+8].blue & 1;
//        
//        unsigned char redLSB10 = img->data[i+9].red & 1;
//        unsigned char blueLSB10 = img->data[i+9].blue & 1;
//        
//        unsigned char redLSB11 = img->data[i+10].red & 1;
//        unsigned char blueLSB11 = img->data[i+10].blue & 1;
//        
//        unsigned char redLSB12 = img->data[i+11].red & 1;
//		unsigned char blueLSB12 = img->data[i+11].blue & 1;
//		
//		lsbsem3[0] = redLSB9;
//		lsbsem3[1] = blueLSB9;
//		lsbsem3[2] = redLSB10;
//		lsbsem3[3] = blueLSB10;
//		lsbsem3[4] = redLSB11;
//		lsbsem3[5] = blueLSB11;
//		lsbsem3[6] = redLSB12;
//		lsbsem3[7] = blueLSB12;
//		
//
//		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
//		for (int q = 0; q < 8; q++) {
//		    combinedValue3 |= lsbsem3[q] << (7 - q);
//		}
//		
//		
		
//		printf("combine value : %d\n", combinedValue);
		
		printf("%c", combinedValue1);
//		printf("%c", combinedValue2);
//		printf("%c", combinedValue3);

		
		
//        memset(lsbsem1, 0, sizeof(lsbsem1));
//        memset(lsbsem2, 0, sizeof(lsbsem2));
//        memset(lsbsem3, 0, sizeof(lsbsem3));
//        
        
        

		
    }
}


void extractLSB(const BMPImage *img, int len) {
    if (!img) {
        fprintf(stderr, "Invalid input\n");
        return;
    }
    
    
	unsigned char lsbsem1[8], lsbsem2[8], lsbsem3[8];

    for (int i = 8; i <= len; i += 8) {
    	unsigned char combinedValue1 = 0;
		unsigned char combinedValue2 = 0;
		unsigned char combinedValue3 = 0;
		
        unsigned char redpixel1 = img->data[i].red & 1;
        unsigned char greenpixel1 = img->data[i].green & 1;
        unsigned char bluepixel1 = img->data[i].blue & 1;
        
        unsigned char redpixel2 = img->data[i+1].red & 1;
        unsigned char greenpixel2 = img->data[i+1].green & 1;
        unsigned char bluepixel2 = img->data[i+1].blue & 1;
        
        unsigned char redpixel3 = img->data[i+2].red & 1;
        unsigned char greenpixel3 = img->data[i+2].green & 1;
        lsbsem1[0] = redpixel1;
		lsbsem1[1] = greenpixel1;
		lsbsem1[2] = bluepixel1;
		lsbsem1[3] = redpixel2;
		lsbsem1[4] = greenpixel2;
		lsbsem1[5] = bluepixel2;
		lsbsem1[6] = redpixel3;
		lsbsem1[7] = greenpixel3;
		

		// Gabungkan setiap elemen dari lsbsem1 menjadi satu nilai unsigned char
		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}

		
		
		


        
        unsigned char bluepixel3 = img->data[i+2].blue & 1;
        
        unsigned char redpixel4 = img->data[i+3].red & 1;
        unsigned char greenpixel4 = img->data[i+3].green & 1;
        unsigned char bluepixel4 = img->data[i+3].blue & 1;
        
        unsigned char redpixel5 = img->data[i+4].red & 1;
        unsigned char greenpixel5 = img->data[i+4].green & 1;
        unsigned char bluepixel5 = img->data[i+4].blue & 1;
        
        unsigned char redpixel6 = img->data[i+5].red & 1;
        
        lsbsem2[0] = bluepixel3;
		lsbsem2[1] = redpixel4;
		lsbsem2[2] = greenpixel4;
		lsbsem2[3] = bluepixel4;
		lsbsem2[4] = redpixel5;
		lsbsem2[5] = greenpixel5;
		lsbsem2[6] = bluepixel5;
		lsbsem2[7] = redpixel6;

		
		for (int q = 0; q < 8; q++) {
		    combinedValue2 |= lsbsem2[q] << (7 - q);
		}
	
        
        
        
        unsigned char greenpixel6 = img->data[i+5].green & 1;
        unsigned char bluepixel6 = img->data[i+5].blue & 1;
        
        unsigned char redpixel7 = img->data[i+6].red & 1;
        unsigned char greenpixel7 = img->data[i+6].green & 1;
        unsigned char bluepixel7 = img->data[i+6].blue & 1;
        
        unsigned char redpixel8 = img->data[i+7].red & 1;
        unsigned char greenpixel8 = img->data[i+7].green & 1;
        unsigned char bluepixel8 = img->data[i+7].blue & 1;
        
        lsbsem3[0] = greenpixel6;
		lsbsem3[1] = bluepixel6;
		lsbsem3[2] = redpixel7;
		lsbsem3[3] = greenpixel7;
		lsbsem3[4] = bluepixel7;
		lsbsem3[5] = redpixel8;
		lsbsem3[6] = greenpixel8;
		lsbsem3[7] = bluepixel8;
		

        
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
    int panjangpesan;

    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    // Mengambil bit terakhir dari setiap byte dalam komponen warna
    int dataSize = image->width * image->height;
    panjangpesan = extractinfolen(image);
    panjangpesan = panjangpesan * 4 + 8;
//    extractLSB(image, panjangpesan);
//	extractredblue(image, panjangpesan);
	extractlsbinfolen(image, panjangpesan);
		
//	printf("\npanjang pesan adalah : %d", panjangpesan);
    // Membebaskan memori yang digunakan oleh gambar dan data bit terakhir
    free(image->data);
    free(image);

    return 0;
}