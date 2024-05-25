#include "lsbjpeg.h"


void open_image(const char *filename, JPEGImageData *image) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("| ERROR: Cannot open source image\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    image->buffer_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    image->buffer = (uint8_t *)malloc(image->buffer_size);
    if (!image->buffer) {
        printf("| ERROR: Memory allocation failed\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(image->buffer, 1, image->buffer_size, file);
    fclose(file);
}

void close_image(JPEGImageData *image) {
    free(image->buffer);
}

void encodeJPEG(const char *source_image, const char *dest_image, utama *var, Enkripsi *En) {
    JPEGImageData image;
    open_image(source_image, &image);
	
    FILE *outfile = fopen(dest_image, "wb");
    if (!outfile) {
        printf("| ERROR: Cannot open destination file\n");
        close_image(&image);
        exit(EXIT_FAILURE);
    }

    uint8_t *buffer = image.buffer;
    size_t buffer_size = image.buffer_size;

    // Menambahkan terminator pada pesan
    size_t message_length = var->isipesan;
    size_t total_message_length = message_length ; 

    // Memeriksa apakah pesan dapat disisipkan dalam gambar
    if (total_message_length * 8 > buffer_size) {
        printf("| ERROR: Need larger file size\n");
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
    fwrite(En->pesanEncrypt, 1, message_length, outfile);
    fwrite("$t3g0", 1, strlen("$t3g0"), outfile); // Mengganti MESSAGE_TERMINATOR

    fclose(outfile);
    close_image(&image);

//    printf("Image Encoded Successfully\n");
}

void decodeJPEG(const char *image_path, char lsbjpg[]) {
    JPEGImageData image;
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

            
            if (!lsbjpg) {
                printf("| ERROR: Memory allocation failed\n");
                close_image(&image);
                exit(EXIT_FAILURE);
            }

            memcpy(lsbjpg, &buffer[pos + 4], message_length);
            lsbjpg[message_length] = '\0';

            printf("| Pesan Hasil Ekstrak LSB: %s\n", lsbjpg);

            //free(lsbjpg);
            break;
        }
        pos++;
    }

    if (pos >= buffer_size - 4) {
        printf("| No Hidden Message Found\n");
    }

    close_image(&image);
}
