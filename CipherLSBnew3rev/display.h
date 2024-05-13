#ifndef display_h
#define display_h
#include "lsbbmp.h"
#include "cipher.h"
#include "bmpio.h"
#include "ws.h"



void displayMenu (int *j);
void encryptBMP (int *j, Enkripsi *En, utama *var);
void decryptBMP (int *j, Enkripsi *En, utama *var, Dekripsi *De);
void encryptJPEG (int *j, Enkripsi *En, utama *var);
void decryptJPEG (int *j, Enkripsi *En, utama *var, Dekripsi *De);
void whitespace (int *j);
void displayencrypt (int *j);
void displaydecrypt (int *j);
void mustintdisplay(int *hasil);

#endif
