#ifndef display_h
#define display_h
#include "lsbbmp.h"
#include "cip.h"
#include "bmpio.h"
#include "ws.h"



void display1 (int *j);
void display2 (int *j, Enkripsi *En, utama *var);
void display3 (int *j, Enkripsi *En, utama *var, Dekripsi *De);
void display4 (int *j, Enkripsi *En, utama *var);
void display5 (int *j, Enkripsi *En, utama *var, Dekripsi *De);
void display6 (int *j);
void displayencrypt (int *j);
void displaydecrypt (int *j);
void mustintdisplay(int *hasil);

#endif
