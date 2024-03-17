#include "bmpio.h"

int main(){
	BMPHeader head;
	BMPImage *bmp = readBMP("sample.bmp", &head);
//	printf("Signature: 0x%X\n", head.signature);
//	printf("File Size: %u bytes\n", head.fileSize);
//	printf("Reserved 1: %u\n", head.reserved1);
//	printf("Reserved 2: %u\n", head.reserved2);
//	printf("Data Offset: %u bytes\n", head.dataOffset);
//	printf("Header Size: %u bytes\n", head.headerSize);
//	printf("Width: %d pixels\n", head.width);
//	printf("Height: %d pixels\n", head.height);
//	printf("Planes: %u\n", head.planes);
//	printf("Bits per Pixel: %u\n", head.bitsPerPixel);
//	printf("Compression: %u\n", head.compression);
//	printf("Data Size: %u bytes\n", head.dataSize);
//	printf("Horizontal Resolution: %d pixels per meter\n", head.hResolution);
//	printf("Vertical Resolution: %d pixels per meter\n", head.vResolution);
//	printf("Colors: %u\n", head.colors);
//	printf("Important Colors: %u\n", head.importantColors);
	writeBMP("sample1.bmp", bmp, head);
	
	return 0;
}
