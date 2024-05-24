#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef ws_h
#define ws_h

typedef struct {
    char delimiter[4];
    char character_set[2][2];
} WhitespaceSteganography;

void init_stegano(WhitespaceSteganography *ws_stegano);
char *encrypt(char *text, char *msg, WhitespaceSteganography *ws_stegano);
char *decrypt(char *text, WhitespaceSteganography *ws_stegano);
void main_ws();

#endif
