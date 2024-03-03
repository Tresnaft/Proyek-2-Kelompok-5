#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int size;
} BITMAPINFOHEADER;

typedef struct {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
} PIXEL;

unsigned int dectobiner(unsigned int n) {
    unsigned int biner = 0, temp = 1;
    while (n != 0) {
        biner += (n % 2) * temp;
        n /= 2;
        temp *= 10;
    }
    return biner;
}

int get_LSB(unsigned char byte){
	return byte & 0x01;
}

int main() {
    FILE *image;
    FILE *target;
    char fpath[1000];
    BITMAPINFOHEADER bih;

    int i = 0;

    printf("Enter BMP file path: ");
    scanf("%s", fpath);
    image = fopen(fpath, "rb");
	printf("Enter BMP target file path: ");
	scanf("%s", fpath);
    target = fopen(fpath, "wb");
    while (image == NULL) {
        printf("Error! Unable to open file. Enter path again: ");
        scanf("%s", fpath);
        image = fopen(fpath, "rb");
    }

    fseek(image, 2, SEEK_SET);
    fread(&bih.size, 4, 1, image);
    /*printf("\nSize of the image = %d\n", bih.size);*/
    

    fseek(image, 18, SEEK_SET);
    fread(&bih.width, 4, 1, image);
    fseek(image, 22, SEEK_SET);
    fread(&bih.height, 4, 1, image);
    /*printf("Width of the image = %d\nHeight of the image = %d\n\n", bih.width, bih.height);*/

    PIXEL pic[bih.width * bih.height]; 



    while (fread(&pic[i], sizeof(PIXEL), 1, image) == 1) {
       /* printf("%d = %u | %u | %u\n", i, dectobiner(pic[i].blue), dectobiner(pic[i].green), dectobiner(pic[i].red) );*/
		printf("%d = %u | %u | %u\n", i, get_LSB(pic[i].blue), get_LSB(pic[i].green), get_LSB(pic[i].red) );
        i++;
    }
    
    unsigned char byte[bih.width * bih.height];

	rewind(image);
	while (fread(&byte, sizeof(unsigned char), 1, image)==1){
		byte[i] = (*byte & 0xFE) | (i & 0x01);
		fwrite(byte, sizeof(unsigned char), 1, target);
	}
	
	fclose(target);
    fclose(image);
    return 0;
}
