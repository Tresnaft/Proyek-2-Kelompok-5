#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ws.h"

void init_stegano(WhitespaceSteganography ws_stegano) {
    strcpy(ws_stegano.delimiter, "\n\t\t\t");
    strcpy(ws_stegano.character_set[0], " ");
    strcpy(ws_stegano.character_set[1], "\t");
}

char *encrypt(char *text, char *msg, WhitespaceSteganography ws_stegano) {
    int msg_len = strlen(msg);
    int text_len = strlen(text);
    int code_len = msg_len * 8;
    char *code = (char *)malloc(code_len + 1);
    memset(code, 0, code_len + 1);

    int bit_mask = 1;
    for (int i = 0; i < msg_len; i++) {
        unsigned char by = msg[i];
        for (int j = 0; j < 8; j++) {
            int m_byte = by & bit_mask;
            by = by >> 1;
            if (m_byte == 0) {
                strncat(code, ws_stegano.character_set[0], 1);
            } else {
                strncat(code, ws_stegano.character_set[1], 1);
            }
        }
    }

    strcat(text, ws_stegano.delimiter);
    strcat(text, code);

    return text;
}

char *decrypt(char *text, WhitespaceSteganography ws_stegano) {
    char *delimiter_pos = strchr(text, ws_stegano.delimiter[0]);
    if (delimiter_pos ==NULL) {
        fprintf(stderr, "Delimiter not found\n");
        exit(1);
    }

    char *code_start = delimiter_pos + strlen(ws_stegano.delimiter);
    int code_len = strlen(code_start);

    int msg_len = (code_len + 7) / 8;
    unsigned char *msg_bytes = (unsigned char *)malloc(msg_len);
    memset(msg_bytes, 0, msg_len);

    int i = 0;
    int j = 0;
    while (i < code_len) {
        unsigned char m_byte = 0;
        for (int k = 0; k < 8; k++) {
            int bit = 0;
            if (code_start[i] == ws_stegano.character_set[1][0]) {
                bit = 1;
            }
            m_byte = (m_byte >> 1) | (bit << 7);
            i++;
        }
        msg_bytes[j] = m_byte;
        j++;
    }

    char *msg = (char *)malloc(msg_len);
    memset(msg, 0, msg_len);
    strncpy(msg, (char *)msg_bytes, msg_len);

    free(msg_bytes);

    return msg;
}
