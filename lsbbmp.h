#ifndef lsbbmp_h
#define lsbbmp_h

#include "cipher.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "bmpio.h"

BMPImage *readBMP(const char *filename);
void inputMessage(char *message, Enkripsi *En, utama *var);
char* messageToBinary(char* s);
void writeMsg(BMPImage *img, const char *binaryMessage);
void writeBMP(const char *filename, BMPImage *img);
int extractinfolen(const BMPImage *img);
void extractlsb(const BMPImage *img, int len, int panjang, char hasilLSB[]);

#endif
