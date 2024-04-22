#ifndef display_h
#define display_h
#include "lsbbmp.h"
#include "cipher.h"
#include "bmpio.h"
#include "ws.h"

typedef struct{
	int enkripsi[500];
	char pesanEncrypt[500];
}Enkripsi;

typedef struct{
	int dekripsi[500];
	char pesanDecrypt[500];
}Dekripsi;

typedef struct{
	char pesan[500];
	char kunci[4];
	char karakter[79]= " GHIJSXabcdLKMNOPQRef&.%$#ghijklmnopqTUVWr456stuvwxy!<>,zABCDEFYZ1237890_-*@?/";
	
	int kuncitonum[4];
	int pesantonum[500];
	int peslen;
	int isipesan;
}utama;

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
