#ifndef display_h
#define display_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lsbbmp.h"
#include "cip.h"
#include "bmpio.h"
#include "ws.h"
#include "lsbjpeg.h"
#include "linkedlist.h"




void mainMenu (int *j);
void enkripsiBMP (int *j, Enkripsi *En, utama *var);
void dekripsiBMP (int *j, Enkripsi *En, utama *var, Dekripsi *De);
void enkripsiJPEG (int *j, Enkripsi *En, utama *var);
void dekripsiJPEG (int *j, Enkripsi *En, utama *var, Dekripsi *De);
void whitespaceSteganography (int *j);
void displayencrypt (int *j);
void displaydecrypt (int *j);
void mustintdisplay(int *hasil);

#endif
