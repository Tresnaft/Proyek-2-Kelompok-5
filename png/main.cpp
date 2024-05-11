#include <stdio.h>
#include <stdlib.h>
#include "lsbpng.h"
#include "lsbpng.cpp"
int main() {
    printf("--LSB Encryption--\n");
    printf("1: Encode\n");
    printf("2: Decode\n");
    printf("Enter your choice: ");
    
    char choice;
    scanf(" %c", &choice); // Notice the space before %c to consume any leading whitespace

    if (choice == '1') {
        char src_image[100], dest_image[100], message[1000];
        printf("Enter Source Image Path: ");
        scanf("%s", src_image);
        printf("Enter Message to Hide: ");
        getchar(); // Clear newline from buffer
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline character
        printf("Enter Destination Image Path: ");
        scanf("%s", dest_image);
        printf("Encoding...\n");
        encode(src_image, dest_image, message);
    } else if (choice == '2') {
        char src_image[100];
        printf("Enter Source Image Path: ");
        scanf("%s", src_image);
        printf("Decoding...\n");
        decode(src_image);
    } else {
        printf("ERROR: Invalid option chosen\n");
    }

    return 0;
}
