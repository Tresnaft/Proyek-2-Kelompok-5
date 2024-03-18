#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ws.h"
#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	WhitespaceSteganography ws_stegano;
    init_stegano();

    char text[100];
    char msg[100];

    printf("Enter cover text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter secret message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    char *encrypted_text = encrypt(text, msg);
    printf("Encrypted text: %s\n", encrypted_text);

    char *decrypted_msg = decrypt(encrypted_text);
    printf("Decrypted message: %s\n", decrypted_msg);
    
    return 0;
}
