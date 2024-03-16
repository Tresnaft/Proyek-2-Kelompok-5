#ifndef CIPHER_H
#define CIPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <string.h>

#define MAX_MESSAGE_LENGTH 2048


typedef struct{
	char pesan[500];
	char kunci[4];
	char karakter[79]= " GHIJSXabcdLKMNOPQRef&.%$#ghijklmnopqTUVWr456stuvwxy!<>,zABCDEFYZ1237890_-*@?/";
	int kuncitonum[4];
	int pesantonum[500];
	int peslen;
	int isipesan;
}utama;

typedef struct{
	int enkripsi[500];
	char pesanEncrypt[500];
}Enkripsi;

typedef struct{
	int dekripsi[500];
	char pesanDecrypt[500];
}Dekripsi;

typedef struct {
    unsigned char red, green, blue;
}RGBPixel;

typedef struct {
    int width, height;
    RGBPixel *data;
}BMPImage;


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

int arr1[MAX_MESSAGE_LENGTH];
int arr2[MAX_MESSAGE_LENGTH];
int arr3[MAX_MESSAGE_LENGTH];

int size1;
int size2;
int size3;
const char *filename_read = "sample.bmp";
const char *filename_write = "sampleout.bmp";
char message[MAX_MESSAGE_LENGTH];
char *binaryMessage[MAX_MESSAGE_LENGTH * 8];
char *output[MAX_MESSAGE_LENGTH];
char mergestring;

void prosesMessage(char *message, Enkripsi *En);
char* messageToBinary(char* s);
BMPImage *readBMP(const char *filename);
void writeMsg(BMPImage *img, const char *binaryMessage);
void writeBMP(const char *filename, BMPImage *img);

BMPImage *readBMP(const char *filename);
int extractinfolen(const BMPImage *img);
void extractlsbinfolen(const BMPImage *img, int len, int panjang);
//int* mergeArrays(int arr1[], int arr2[], int arr3[], int size1, int size2, int size3);
//void rgbPixelToString(const RGBPixel *pixel, char *output);

void cetak_pesan_encrypt(Enkripsi *En, utama *var);
void cetak_matriks_encrypt(utama *var, Enkripsi *En);
void cetak_pesan_decrypt(Dekripsi *De, utama *var);
void cetak_matriks_decrypt(utama *var, Dekripsi *De);
void pesan_encrypt(Enkripsi *En, utama *var);
void pesan_decrypt(Dekripsi *De, utama *var);
void matriks_pesan(utama *var);
void matriks_kunci(utama *var);
void cetak_matriks_pesan(utama *var);
void cetak_matriks_kunci(utama *var);
void Encrypt(Enkripsi *En, utama *var);
int determinan(int kunci[]);
void invers_matriks(int kunci[], int invers[]);
int Zinv(int angka);
int modulus(int angka);
void Decrypt(utama *var, Enkripsi *En, Dekripsi *De);
void tampilan(utama *var, Enkripsi *En, Dekripsi *De, BMPImage *image);

/*========================LSB Extract===================*/






/*==============End of LSB Extract==================*/

/*========================LSB Input=======================*/

/*=================End of LSB Input=========================*/

#endif 
