#ifndef display_h
#define display_h

#include "lsbpng.h"
#include "lsbbmp.h"
#include "cip.h"
#include "bmpio.h"
#include "ws.h"
#include "lsbjpeg.h"
#include "linkedlist.h"

void clearInputBuffer();
void intInput (int *j, bool *valid);
void displayMenu (int *j, bool *valid);
void encryptBMP(Enkripsi *En, utama *var);
void decryptBMP(Enkripsi *En, utama *var, Dekripsi *De);
void encryptJPEG(Enkripsi *En, utama *var);
void decryptJPEG(Enkripsi *En, utama *var, Dekripsi *De);
//void whitespace ();
void displayencrypt(int *j, bool *valid);
void displaydecrypt(int *j, bool *valid);
void mustintdisplay(int *hasil);
void encryptPNG(Enkripsi *En, utama *var);
void decryptPNG(Dekripsi *De, utama *var);

#endif
