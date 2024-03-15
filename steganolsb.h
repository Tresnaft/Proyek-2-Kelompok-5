#ifndef steganolsb_h
#define steganolsb_h
#include <stdint.h>


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

BMPImage *readBMP(const char *filename);
void inputMessage(char *message);
char* messageToBinary(char* s);
void writeMsg(BMPImage *img, const char *binaryMessage);
void writeBMP(const char *filename, BMPImage *img);
int extractinfolen(const BMPImage *img);
void extractlsb(const BMPImage *img, int len);

#endif