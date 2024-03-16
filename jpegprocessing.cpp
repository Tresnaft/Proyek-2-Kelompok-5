#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "image.h"

#define MESSAGE_TERMINATOR "$t3g0"

typedef struct {
    uint8_t *buffer;
    size_t buffer_size;
} ImageData;

void open_image(const char *filename, ImageData *image) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("ERROR: Cannot open source image\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    image->buffer_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    image->buffer = (uint8_t *)malloc(image->buffer_size);
    if (!image->buffer) {
        printf("ERROR: Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(image->buffer, 1, image->buffer_size, file);
    fclose(file);
}

void close_image(ImageData *image) {
    free(image->buffer);
}

void encode(const char *source_image, const char *dest_image, const char *message) {
    ImageData image;
    open_image(source_image, &image);

    FILE *outfile = fopen(dest_image, "wb");
    if (!outfile) {
        printf("ERROR: Cannot open destination file\n");
        close_image(&image);
        exit(EXIT_FAILURE);
    }

    uint8_t *buffer = image.buffer;
    size_t buffer_size = image.buffer_size;

    // Menambahkan terminator pada pesan
    size_t message_length = strlen(message);
    size_t total_message_length = message_length + strlen(MESSAGE_TERMINATOR);

    // Memeriksa apakah pesan dapat disisipkan dalam gambar
    if (total_message_length * 8 > buffer_size) {
        printf("ERROR: Need larger file size\n");
        close_image(&image);
        fclose(outfile);
        exit(EXIT_FAILURE);
    }

    // Menyalin semua data dari gambar ke gambar yang akan disimpan
    fwrite(buffer, 1, buffer_size, outfile);

    // Menambahkan marker COM (Comment) untuk menyimpan panjang pesan
    uint16_t message_length_be = total_message_length;
    fwrite("\xFF\xFE", 1, 2, outfile); // Marker COM
    fwrite(&message_length_be, sizeof(uint16_t), 1, outfile); // Panjang pesan

    // Menambahkan pesan
    fwrite(message, 1, message_length, outfile);
    fwrite(MESSAGE_TERMINATOR, 1, strlen(MESSAGE_TERMINATOR), outfile);

    fclose(outfile);
    close_image(&image);

    printf("Image Encoded Successfully\n");
}

void decode(const char *image_path) {
    ImageData image;
    open_image(image_path, &image);

    uint8_t *buffer = image.buffer;
    size_t buffer_size = image.buffer_size;

    // Mencari panjang pesan dalam komentar
    size_t pos = 0;
    while (pos < buffer_size - 4) {
        if (buffer[pos] == 0xFF && buffer[pos + 1] == 0xFE) {
            uint16_t message_length_be;
            memcpy(&message_length_be, &buffer[pos + 2], sizeof(uint16_t));
            size_t message_length = message_length_be;

            char *message = (char *)malloc(message_length + 1);
            if (!message) {
                printf("ERROR: Memory allocation failed\n");
                close_image(&image);
                exit(EXIT_FAILURE);
            }

            memcpy(message, &buffer[pos + 4], message_length);
            message[message_length] = '\0';

            printf("Hidden Message: %s\n", message);

            free(message);
            break;
        }
        pos++;
    }

    if (pos >= buffer_size - 4) {
        printf("No Hidden Message Found\n");
    }

    close_image(&image);
}

int main() {
    printf("--LSB Encryption--\n");
    printf("1: Encode\n");
    printf("2: Decode\n");

    char choice;
    scanf("%c", &choice);

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

