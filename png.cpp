#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef struct {
    unsigned char *image;
    int width;
    int height;
    int channels;
} ImageData;

// Fungsi untuk memuat gambar dari file
ImageData *loadImage(char *filename) {
    ImageData *img_data = (ImageData *)malloc(sizeof(ImageData));
    img_data->image = stbi_load(filename, &img_data->width, &img_data->height, &img_data->channels, 0);
    if (img_data->image == NULL) {
        printf("Error loading the image.\n");
        free(img_data);
        return NULL;
    }
    return img_data;
}

// Fungsi untuk membebaskan memori yang digunakan untuk gambar
void freeImageData(ImageData *img_data) {
    stbi_image_free(img_data->image);
    free(img_data);
}

// Fungsi untuk menyembunyikan pesan dalam gambar
void hideMessage() {
    char input_image[100];
    char output_image[100];
    char message[1000];

    // Meminta input dari pengguna
    printf("Enter input image filename: ");
    scanf("%s", input_image);

    printf("Enter output image filename: ");
    scanf("%s", output_image);

    printf("Enter message to hide: ");
    getchar(); // Membersihkan karakter newline dari buffer input
    fgets(message, 1000, stdin);
    message[strcspn(message, "\n")] = '\0'; // Menghapus karakter newline di akhir pesan

    // Memuat gambar dari file
    ImageData *img_data = loadImage(input_image);
    if (img_data == NULL)
        return;

    // Menyembunyikan pesan dalam gambar
    int message_length = strlen(message);
    int image_size = img_data->width * img_data->height * img_data->channels;

    if (message_length * 8 > image_size) {
        printf("Message is too large for the image.\n");
        freeImageData(img_data);
        return;
    }

    unsigned char *message_ptr = (unsigned char *)message;

    for (int i = 0; i < message_length; ++i) {
        unsigned char byte = *message_ptr++;
        for (int j = 0; j < 8; ++j) {
            img_data->image[i * 8 + j] &= 0xFE; // Menghapus bit paling tidak signifikan
            img_data->image[i * 8 + j] |= (byte >> j) & 1; // Mengatur bit paling tidak signifikan sesuai dengan pesan
        }
    }

    // Menyimpan gambar yang telah dimodifikasi
    stbi_write_png(output_image, img_data->width, img_data->height, img_data->channels, img_data->image, img_data->width * img_data->channels);

    // Membebaskan memori yang digunakan untuk gambar
    freeImageData(img_data);

    printf("Message hidden successfully in %s.\n", output_image);
}

// Fungsi untuk mengekstrak pesan dari gambar
void extractMessage() {
    char input_image[100];

    // Meminta input dari pengguna
    printf("Enter input image filename: ");
    scanf("%s", input_image);

    // Memuat gambar dari file
    ImageData *img_data = loadImage(input_image);
    if (img_data == NULL)
        return;

    // Mengekstrak pesan dari gambar
    int image_size = img_data->width * img_data->height * img_data->channels;
    int message_length = 0;
    char *message = (char *)malloc(1000 * sizeof(char)); // Mengasumsikan panjang maksimum pesan adalah 1000 karakter
    unsigned char byte = 0;
    int bit_count = 0;

    for (int i = 0; i < image_size; ++i) {
        byte |= (img_data->image[i] & 1) << bit_count;
        ++bit_count;

        if (bit_count == 8) {
            message[message_length++] = byte;
            byte = 0;
            bit_count = 0;
            if (message_length >= 999) // Periksa apakah panjang pesan melebihi batas maksimum
                break;
        }

        // Jika sudah mencapai akhir data gambar dan masih ada bit tersisa di byte terakhir,
        // bit-bit tersebut perlu ditangani secara terpisah.
        if (i == image_size - 1 && bit_count != 0) {
            printf("Incomplete message found.\n");
            free(message);
            freeImageData(img_data);
            return;
        }
    }

    // Menambahkan null terminator pada akhir pesan
    message[message_length] = '\0';

    // Menampilkan pesan yang telah diekstrak
    printf("Extracted Message: %s\n", message);

    // Membebaskan memori yang digunakan untuk pesan dan gambar
    free(message);
    freeImageData(img_data);
}

int main() {
    int choice;

    // Menu utama
    do {
        printf("\nMenu:\n");
        printf("1. Hide Message in Image\n");
        printf("2. Extract Message from Image\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                hideMessage();
                break;
            case 2:
                extractMessage();
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
