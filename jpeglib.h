#ifndef JPEG_READER_H
#define JPEG_READER_H

#include <cstdint>
#include <string>
#include <vector>

struct JPEGHeader {
    uint16_t marker;
    uint16_t length;
};

class JPEGReader {
public:
    JPEGReader(const std::string& filename);
    ~JPEGReader();

    bool isValid() const;

    std::vector<uint8_t> readData();

private:
    std::string filename;
    std::vector<uint8_t> imageData;

    bool validateHeader(const JPEGHeader& header);
    void readHeader(FILE* file, JPEGHeader& header);
    void readImageData(FILE* file, size_t dataSize);
};

#endif // JPEG_READER_H

