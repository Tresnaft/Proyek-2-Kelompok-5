#ifndef CIPHER_H
#define CIPHER_H

#include "lsbbmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>
#include <string.h>
#include "bmpio.h"


#define MAX_MESSAGE_LENGTH 2048





//char hasilLSB[2048];
//int numLSB[2048];

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
void matriks_LSB(utama *var, char hasilLSB[], int numLSB[], int batas);
void Encrypt(Enkripsi *En, utama *var);
int determinan(int kunci[]);
void invers_matriks(int kunci[], int invers[]);
int Zinv(int angka);
int modulus(int angka);
void Decrypt(utama *var, int numLSB[], Dekripsi *De, int batas);
void tampilan(utama *var, Enkripsi *En, Dekripsi *De);
void matriks_key_LSB(char key[], int keytonum[], utama *var);
void cetak_matriks_decryptLSB(int batas, Dekripsi *De);
void pesan_decryptLSB(Dekripsi *De, int batas, utama *var);
void cetak_pesan_decryptLSB(Dekripsi *De, int batas);



#endif 
