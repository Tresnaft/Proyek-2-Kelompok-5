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

void freeImageData(ImageData *img_data) {
    stbi_image_free(img_data->image);
    free(img_data);
}

void encodeLSB(ImageData *img_data, char *message) {
    int message_length = strlen(message);
    int image_size = img_data->width * img_data->height * img_data->channels;

    if (message_length * 8 > image_size) {
        printf("Message is too large for the image.\n");
        return;
    }

    unsigned char *message_ptr = (unsigned char *)message;

    for (int i = 0; i < message_length; ++i) {
        unsigned char byte = *message_ptr++;
        for (int j = 0; j < 8; ++j) {
            img_data->image[i * 8 + j] &= 0xFE; // Clear the least significant bit
            img_data->image[i * 8 + j] |= (byte >> j) & 1; // Set the least significant bit according to the message
        }
    }
}

char *decodeLSB(ImageData *img_data) {
    int image_size = img_data->width * img_data->height * img_data->channels;
    int message_length = 0;
    char *message = (char *)malloc(1000 * sizeof(char)); // Assume the maximum message length is 1000 characters

    for (int i = 0; i < image_size; i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8; ++j) {
            byte |= (img_data->image[i + j] & 1) << j; // Retrieve the least significant bit
        }
        if (byte == '\0') // Assume end of message is marked by null terminator
            break;
        message[message_length++] = byte;
    }
    message[message_length] = '\0'; // Null terminate the string

    return message;
}

int saveImage(ImageData *img_data, char *filename) {
    return stbi_write_png(filename, img_data->width, img_data->height, img_data->channels, img_data->image, img_data->width * img_data->channels);
}

void hideMessage() {
    char input_image[100];
    char output_image[100];
    char message[1000];

    printf("Enter input image filename: ");
    scanf("%s", input_image);

    printf("Enter output image filename: ");
    scanf("%s", output_image);

    printf("Enter message to hide: ");
    getchar(); // Clear the newline character from the input buffer
    fgets(message, 1000, stdin);
    message[strcspn(message, "\n")] = 0; // Remove trailing newline character, if any

    ImageData *img_data = loadImage(input_image);
    if (img_data == NULL)
        return;

    encodeLSB(img_data, message);
    saveImage(img_data, output_image);

    freeImageData(img_data);

    printf("Message hidden successfully in %s.\n", output_image);
}

void extractMessage() {
    char input_image[100];

    printf("Enter input image filename: ");
    scanf("%s", input_image);

    ImageData *img_data = loadImage(input_image);
    if (img_data == NULL)
        return;

    char *decoded_message = decodeLSB(img_data);
    printf("Decoded Message: %s\n", decoded_message);

    freeImageData(img_data);
    free(decoded_message);
}

int main() {
    int choice;

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
