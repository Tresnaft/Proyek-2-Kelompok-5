#ifndef display_h
#define display_h

#include "lsbpng.h"
#include "lsbbmp.h"
#include "cip.h"
#include "bmpio.h"
#include "ws.h"
#include "lsbjpeg.h"
#include "linkedlist.h"

void displayMenu (int *j);
void encryptBMP (Enkripsi *En, utama *var);
void decryptBMP (Enkripsi *En, utama *var, Dekripsi *De);
void encryptJPEG (Enkripsi *En, utama *var);
void decryptJPEG (Enkripsi *En, utama *var, Dekripsi *De);
void whitespace ();
void displayencrypt (int *j);
void displaydecrypt (int *j);
void mustintdisplay(int *hasil);
void encryptPNG();
void decryptPNG();

#endif
