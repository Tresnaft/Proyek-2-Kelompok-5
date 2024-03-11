#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_MESSAGE_LENGTH 2048

typedef struct {
    unsigned char red, green, blue;
} RGBPixel;

typedef struct {
    int width, height;
    RGBPixel *data;
} BMPImage;

#pragma pack(push, 1)
typedef struct {
    uint16_t signature;       // Signature ('BM')
    uint32_t fileSize;        // File size in bytes
    uint16_t reserved1;       // Reserved (unused)
    uint16_t reserved2;       // Reserved (unused)
    uint32_t dataOffset;      // Offset to image data
    uint32_t headerSize;      // Header size (40 bytes)
    int32_t width;            // Image width
    int32_t height;           // Image height
    uint16_t planes;          // Number of color planes (must be 1)
    uint16_t bitsPerPixel;    // Bits per pixel (1, 4, 8, 16, 24, or 32)
    uint32_t compression;     // Compression method (0 for uncompressed)
    uint32_t dataSize;        // Size of raw image data
    int32_t hResolution;      // Horizontal resolution (pixels per meter)
    int32_t vResolution;      // Vertical resolution (pixels per meter)
    uint32_t colors;          // Number of colors in palette
    uint32_t importantColors; // Number of important colors (0 means all)
} BMPHeader;
#pragma pack(pop)

void inputMessage(char *message) {
    printf("Masukkan pesan yang ingin disembunyikan: ");
    fgets(message, MAX_MESSAGE_LENGTH, stdin);
    // Menghapus karakter newline jika ada
    if ((strlen(message) > 0) && (message[strlen(message) - 1] == '\n')) {
        message[strlen(message) - 1] = '\0';
    }
}


char* messageToBinary(char* s) {
    if (s == NULL) return NULL; // Handle NULL input

    size_t len = strlen(s);
    
    char *binary = (char *)malloc(len * 8 + 1); // Allocate memory for binary string
    if (binary == NULL) return NULL; // Check for allocation failure
    binary[0] = '\0';
    for (size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for (int j = 7; j >= 0; --j) {
            if (ch & (1 << j)) {
                strcat(binary, "1");
            } else {
                strcat(binary, "0");
            }
        }
    }
    return binary;
}

BMPImage *readBMP(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    BMPHeader header;
    fread(&header, sizeof(header), 1, file);

    if (header.signature != 0x4D42) {
        fprintf(stderr, "Invalid BMP file format\n");
        fclose(file);
        exit(1);
    }

    if (header.bitsPerPixel != 24) {
        fprintf(stderr, "Unsupported bits per pixel\n");
        fclose(file);
        exit(1);
    }

    BMPImage *img = (BMPImage *)malloc(sizeof(BMPImage));
    if (!img) {
        fprintf(stderr, "Unable to allocate memory\n");
        fclose(file);
        exit(1);
    }

    img->width = header.width;
    img->height = header.height;

    // Set file position to the beginning of image data
    fseek(file, header.dataOffset, SEEK_SET);

    // Allocate memory for image data
    img->data = (RGBPixel *)malloc(sizeof(RGBPixel) * img->width * img->height);
    if (!img->data) {
        fprintf(stderr, "Unable to allocate memory\n");
        fclose(file);
        free(img);
        exit(1);
    }

    // Read image data row by row (from bottom to top)
    int padding = (4 - (img->width * sizeof(RGBPixel)) % 4) % 4; // Padding bytes per row
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            fread(&img->data[y * img->width + x], sizeof(RGBPixel), 1, file);
        }
        // Skip padding bytes
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return img;
}

void writeMsg(BMPImage *img, const char *binaryMessage) {
    int len = strlen(binaryMessage);
    int bitIndex = 0;
    for (int i = 0; i < img->width * img->height; i++) {
        for (int bit = 0; bit < 3; bit++) {
            if (bitIndex < len) {
                unsigned char *color;
                switch (bit) {
                    case 0: color = &img->data[i].red; break;
                    case 1: color = &img->data[i].green; break;
                    case 2: color = &img->data[i].blue; break;
                }
                *color = (*color & 0xFE) | (binaryMessage[bitIndex++] - '0');
            }
        }
    }
}


void writeBMP(const char *filename, BMPImage *img) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Unable to open file '%s'\n", filename);
        exit(1);
    }

    BMPHeader header = {0};
    header.signature = 0x4D42; // BM
    header.fileSize = sizeof(BMPHeader) + (img->width * sizeof(RGBPixel) + ((4 - (img->width * sizeof(RGBPixel)) % 4) % 4)) * img->height;
    header.dataOffset = sizeof(BMPHeader);
    header.headerSize = 40;
    header.width = img->width;
    header.height = img->height;
    header.planes = 1;
    header.bitsPerPixel = 24;
    header.compression = 0;
    header.dataSize = (img->width * sizeof(RGBPixel) + ((4 - (img->width * sizeof(RGBPixel)) % 4) % 4)) * img->height;
    header.hResolution = 0;
    header.vResolution = 0;
    header.colors = 0;
    header.importantColors = 0;

    fwrite(&header, sizeof(header), 1, file);

    int padding = (4 - (img->width * sizeof(RGBPixel)) % 4) % 4; // Padding bytes per row
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            fwrite(&img->data[y * img->width + x], sizeof(RGBPixel), 1, file);
        }
        // Write padding bytes
        for (int p = 0; p < padding; p++) {
            fputc(0, file);
        }
    }

    fclose(file);
}

char *extractMsg(BMPImage *img) {
    int len = (img->width * img->height * 3) / 8; // Panjang pesan dalam byte
    char *binaryMessage = (char *)malloc(len + 1); // alokasi memori untuk pesan
    if (!binaryMessage) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    int bitIndex = 0;
    for (int i = 0; i < img->width * img->height; i++) {
        for (int bit = 0; bit < 3; bit++) {
            unsigned char *color;
            switch (bit) {
                case 0: color = &img->data[i].red; break;
                case 1: color = &img->data[i].green; break;
                case 2: color = &img->data[i].blue; break;
            }
            binaryMessage[bitIndex++] = ((*color) & 1) + '0';
        }
    }
    binaryMessage[len] = '\0'; // Null-terminate the binary string

    char *message = (char *)malloc(len / 8 + 1); // alokasi memori untuk pesan
    if (!message) {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }

    // Mengonversi biner ke ASCII
    for (int i = 0; i < len / 8; i++) {
        char ch = 0;
        for (int j = 0; j < 8; j++) {
            ch |= (binaryMessage[i * 8 + j] - '0') << (7 - j);
        }
        message[i] = ch;
    }
    message[len / 8] = '\0'; // Null-terminate the string

    free(binaryMessage);

    return message;
}

int main() {
    BMPImage *image;
    const char *filename_read = "sample.bmp";
    const char *filename_write = "sampleout.bmp";
    char message[MAX_MESSAGE_LENGTH];
    char *binaryMessage[MAX_MESSAGE_LENGTH * 8];

    // Membaca pesan dari pengguna
    inputMessage(message);

    // Mengonversi pesan menjadi representasi biner
//    messageToBinary(message, binaryMessage);
	
	*binaryMessage = messageToBinary(message);
    // Membaca gambar BMP dari file
    image = readBMP(filename_read);

    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    // Menulis pesan ke dalam gambar
    writeMsg(image, *binaryMessage);

    // Menulis gambar dengan pesan ke file
    writeBMP(filename_write, image);

	printf("berhasil\n");

    // Membebaskan memori yang digunakan oleh gambar dan pesan yang diekstraksi
    free(image->data);
    free(image);
//    free(extracted_message);

    return 0;
}
