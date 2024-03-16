BMPImage *image;
    const char *filename_read = "sample.bmp";
    const char *filename_write = "sampleout.bmp";
    char message[MAX_MESSAGE_LENGTH];
    char *binaryMessage[MAX_MESSAGE_LENGTH * 8];

    inputMessage(message);
	
	*binaryMessage = messageToBinary(message);
    image = readBMP(filename_read);

    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    writeMsg(image, *binaryMessage);

    writeBMP(filename_write, image);

	printf("berhasil\n");

    free(image->data);
    free(image);