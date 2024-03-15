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

// algoritma infolen
void extractlsbinfolen(const BMPImage *img, int len, int panjang) {
	char* dekripsi = (char* ) malloc (panjang * sizeof(char));
	char tes;

    if (!img) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    char combinedValue[panjang]; // Array karakter untuk menyimpan combinedValue1

    int index = 0; // Indeks untuk menyimpan nilai ke dalam array combinedValues
    

    
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





int main() {
    BMPImage *image;
    const char *filename_read = "sampleout.bmp";
    printf("%s\n", filename_read);
    // Membaca gambar BMP dari file
    image = readBMP(filename_read);
    int panjangpesan;
    int reallen;

    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    // Mengambil bit terakhir dari setiap byte dalam komponen warna
    int dataSize = image->width * image->height;
    panjangpesan = extractinfolen(image);
    reallen = panjangpesan;
    panjangpesan = panjangpesan * 4 + 8;
//    extractLSB(image, panjangpesan);
//	extractredblue(image, panjangpesan);
	extractlsbinfolen(image, panjangpesan, reallen);
		
//	printf("\npanjang pesan adalah : %d", panjangpesan);
    // Membebaskan memori yang digunakan oleh gambar dan data bit terakhir
    free(image->data);
    free(image);

    return 0;
}