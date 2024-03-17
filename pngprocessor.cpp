#include "pngprocessor.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdlib.h>
#include <string.h>

Image* loadImage(const char* filename) {
    Image* image = (Image*)malloc(sizeof(Image));
    if (!image) {
        printf("Failed to allocate memory for image.\n");
        return NULL;
    }

    image->image_data = stbi_load(filename, &image->width, &image->height, &image->channels, 0);
    if (!image->image_data) {
        printf("Failed to load image.\n");
        free(image);
        return NULL;
    }

    return image;
}

void hideMessage(Image* image, const char* message) {
    int message_length = strlen(message);
    if (message_length * 8 > image->width * image->height * image->channels) {
        printf("Message is too large to be hidden in the image.\n");
        return;
    }

    int char_index = 0;
    for (int i = 0; i < image->width * image->height * image->channels; ++i) {
        for (int j = 0; j < 3; ++j) { // Loop over RGB channels
            if (char_index < message_length) {
                image->image_data[i * 3 + j] &= 0xFE; // Clear the LSB
                image->image_data[i * 3 + j] |= (message[char_index] >> (7 - j)) & 1; // Set the LSB to the message bit
            } else {
                break;
            }
        }
        if (char_index >= message_length) {
            break;
        }
        char_index++;
    }
}

char* extractMessage(Image* image) {
    char* extracted_message = (char*)malloc(image->width * image->height * image->channels / 8 + 1);
    if (!extracted_message) {
        printf("Failed to allocate memory for extracted message.\n");
        return NULL;
    }

    int char_index = 0;
    char current_char = 0;
    for (int i = 0; i < image->width * image->height * image->channels; ++i) {
        for (int j = 0; j < 3; ++j) { // Loop over RGB channels
            current_char <<= 1;
            current_char |= image->image_data[i * 3 + j] & 1;
            if ((i * 3 + j + 1) % 8 == 0) { // If we have extracted a full character
                extracted_message[char_index++] = current_char;
                current_char = 0;
            }
        }
    }
    extracted_message[char_index] = '\0'; // Null terminate the string
    return extracted_message;
}

void saveImage(const char* filename, Image* image) {
    stbi_write_png(filename, image->width, image->height, image->channels, image->image_data, image->width * image->channels);
}

void freeImage(Image* image) {
    stbi_image_free(image->image_data);
    free(image);
}

