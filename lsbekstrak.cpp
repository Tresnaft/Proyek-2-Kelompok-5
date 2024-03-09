#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cstring>

typedef struct {
    unsigned char red, green, blue;
} RGBPixel;

typedef struct {
    int width, height;
    RGBPixel *data;
} BMPImage;

#pragma pack(push, 1)
typedef struct {
    uint16_t signature;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t dataOffset;
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t dataSize;
    int32_t hResolution;
    int32_t vResolution;
    uint32_t colors;
    uint32_t importantColors;
} BMPHeader;
#pragma pack(pop)

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

    fseek(file, header.dataOffset, SEEK_SET);

    img->data = (RGBPixel *)malloc(sizeof(RGBPixel) * img->width * img->height);
    if (!img->data) {
        fprintf(stderr, "Unable to allocate memory\n");
        fclose(file);
        free(img);
        exit(1);
    }

    int padding = (4 - (img->width * sizeof(RGBPixel)) % 4) % 4;
    for (int y = img->height - 1; y >= 0; y--) {
        for (int x = 0; x < img->width; x++) {
            fread(&img->data[y * img->width + x], sizeof(RGBPixel), 1, file);
        }
        fseek(file, padding, SEEK_CUR);
    }

    fclose(file);
    return img;
}

void extractLSB(const BMPImage *img, unsigned char *lsbData) {
    if (!img || !lsbData) {
        fprintf(stderr, "Invalid input\n");
        return;
    }

    int dataIndex = 0;
    for (int i = 0; i < img->width * img->height; i++) {
        unsigned char redLSB = img->data[i].red & 1;
        unsigned char greenLSB = img->data[i].green & 1;
        unsigned char blueLSB = img->data[i].blue & 1;

        // Susun ulang bit-bit terakhir menjadi satu byte
        unsigned char outputByte = (redLSB << 2) | (greenLSB << 1) | blueLSB;

        // Simpan outputByte ke dalam lsbData
        lsbData[dataIndex++] = outputByte;
    }
}


void combineLSB(const unsigned char *lsbData, int dataSize) {

    if (!lsbData) {
        fprintf(stderr, "Invalid input\n");
        return;
    }

    printf("Kumpulan bit terakhir (berurutan dari kiri ke kanan):\n");
    for (int i = 0; i < dataSize; i++) {
        printf("%d", (lsbData[i] >> 2) & 1);
        printf("%d", (lsbData[i] >> 1) & 1);
        printf("%d", lsbData[i] & 1);
    }
    printf("\n");
}



void convertToASCII(const unsigned char *lsbData, int dataSize) {
    if (!lsbData || dataSize % 8 != 0) {
        fprintf(stderr, "Invalid input\n");
        return;
    }

    printf("Karakter ASCII yang dihasilkan dari setiap 8 bit (1 byte):\n");
    for (int i = 0; i < dataSize; i += 8) {
        unsigned char byte = 0;
        for (int j = 0; j < 8; j++) {
            byte |= lsbData[i + j] << (7 - j);
        }
        printf("%c", byte);
    }
    printf("\n");
}



int main() {
    BMPImage *image;
    const char *filename_read = "sampleout.bmp";
    printf("%s\n", filename_read);
    // Membaca gambar BMP dari file
    image = readBMP(filename_read);

    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    // Mengambil bit terakhir dari setiap byte dalam komponen warna
    int dataSize = image->width * image->height;
    unsigned char *lsbData = (unsigned char *)malloc(dataSize * sizeof(unsigned char));
    extractLSB(image, lsbData);

    // Menggabungkan semua bit terakhir secara berurutan
    combineLSB(lsbData, dataSize);

    // Mengonversi setiap 8 bit menjadi ASCII dan menampilkan hasilnya
    convertToASCII(lsbData, dataSize);

    // Membebaskan memori yang digunakan oleh gambar dan data bit terakhir
    free(image->data);
    free(image);
    free(lsbData);

    return 0;
}

// Pisahkan bit yang dibaca per 8 bit agar bisa di konversi kedalam ascii