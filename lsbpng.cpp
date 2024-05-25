#include "lsbpng.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

PNGImageData *loadImage(char *filename) {
    PNGImageData *img_data = (PNGImageData *)malloc(sizeof(PNGImageData));
    if (!img_data) {
        printf("| Memory allocation failed.\n");
        return NULL;
    }
    
    // Load image using STB library
    img_data->image = stbi_load(filename, &img_data->width, &img_data->height, &img_data->channels, 0);
    if (img_data->image == NULL) {
        printf("| Error loading the image.\n");
        free(img_data);
        return NULL;
    }
    
    return img_data;
}

void freeImageData(PNGImageData *img_data) {
    stbi_image_free(img_data->image);
    free(img_data);
}

void encodePNG(char *src_image, char *dest_image, char *message) {
    // Load the source image
    PNGImageData *img_data = loadImage(src_image);
    if (img_data == NULL)
        return;

    int image_size = img_data->width * img_data->height * img_data->channels;

    // Append message terminator
    strcat(message, "$t3g0");
    int message_length = strlen(message);
    int required_pixels = message_length * 8;

    if (required_pixels > image_size) {
        printf("| ERROR: Need larger file size\n");
        freeImageData(img_data);
        return;
    }

    // Embed message into the image
    int bit_index = 0;
    for (int i = 0; i < image_size && bit_index < required_pixels; ++i) {
        for (int j = 0; j < 3 && bit_index < required_pixels; ++j) {
            img_data->image[i * 3 + j] &= 0xFE; // Clear the least significant bit
            img_data->image[i * 3 + j] |= (message[bit_index / 8] >> (7 - (bit_index % 8))) & 1; // Embed bit from message
            ++bit_index;
        }
    }

    // Write the modified image to file
    stbi_write_png(dest_image, img_data->width, img_data->height, img_data->channels, img_data->image, img_data->width * img_data->channels);

    // Free memory used by the image
    freeImageData(img_data);

//    printf("Image Encoded Successfully\n");

}


void decodePNG(char *src_image, char *message) {
        // Load the source image
    PNGImageData *img_data = loadImage(src_image);
    if (img_data == NULL)
        return;

    int image_size = img_data->width * img_data->height * img_data->channels;

    char decoded_message[1000] = {0}; // Initialize the decoded message buffer

    int bit_index = 0;
    for (int i = 0; i < image_size && bit_index < 1000 * 8; ++i) {
        for (int j = 0; j < 3 && bit_index < 1000 * 8; ++j) {
            decoded_message[bit_index / 8] |= (img_data->image[i * 3 + j] & 1) << (7 - (bit_index % 8)); // Extract bit from image and store it in the decoded message
            ++bit_index;
        }
    }

    // Find message terminator
    char *terminator_pos = strstr(decoded_message, "$t3g0");
    if (terminator_pos != NULL) {
        *terminator_pos = '\0'; // Null-terminate the decoded message at the terminator position
        printf("| Decoded Message: %s\n", decoded_message);
    } else {
        printf("| No Hidden Message Found\n");
    }

    strcpy(message, decoded_message);
    // Free memory used by the image
    freeImageData(img_data);

}

