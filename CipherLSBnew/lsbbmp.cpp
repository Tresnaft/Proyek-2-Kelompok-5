#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MAX_MESSAGE_LENGTH 2048
#include "lsbbmp.h"
#include "bmpio.h"




void inputMessage(char *message, Enkripsi *En, utama *var) {
    int messageLength;
    char str[MAX_MESSAGE_LENGTH];
    int i;

	
	messageLength = var->isipesan;
//	printf("%d", var->isipesan);
	//strlen(En->pesanEncrypt) + 1;
    // Menghitung jumlah byte dalam pesan
    //int messageLength = sizeof(En->pesanEncrypt) / sizeof(En->pesanEncrypt[0]);
	 // Jumlah byte termasuk karakter null terminator
    if (messageLength % 10 == 0){
    	messageLength+=1;
	}
	if(messageLength % 10 == 9){
		messageLength+=2;
	}
    
    sprintf(str, "%d", messageLength); // Menyimpan messageLength sebagai karakter ke dalam str
//    printf("\nprint str %s\n", str); // Cetak str sebagai string, bukan sebagai satu karakter

    // Menyalin pesan ke array message dimulai dari indeks ke-1
    message[0] = str[0];
    message[1] = str[1];
    message[2] = str[2];
    
    if (message[1] == 0) {
    	message[1] = 48;
	}
	if (message[2] == 0) {
    	message[2] = 48;
	}
    
//    printf("message 0 : %d\n", message[0]);
//    printf("message 1 : %d\n", message[1]);
//    printf("message 2 : %d\n", message[2]);
    
    for (i = 3; i < messageLength + 3; i++) {
        message[i] = En->pesanEncrypt[i - 3];
        
    }
//    for (i = 0; i < messageLength + 1; i++) {
//    	printf("%c", message[i]);
//	}
}

char* messageToBinary(char* s) {
    if (s == NULL) return NULL; // Handle NULL input

    int len = strlen(s);
    
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

void writeMsg(BMPImage *img, const char *binaryMessage) {
    int len = strlen(binaryMessage);
    int bitIndex = 0;
    for (int i = 0; i < img->width * img->height; i++) {
 	for (int bit = 0; bit < 2; bit++) {
            if (bitIndex < len) {
                unsigned char *color;
                switch (bit) {
                    case 0: color = &img->data[i].red; break;
                    case 1: color = &img->data[i].blue; break;
                }
                *color = (*color & 0xFE) | (binaryMessage[bitIndex++] - '0');
	    	}
		}
	}
}


int extractinfolen(const BMPImage *img) {
	unsigned char combinedValue1 = 0;
	unsigned char combinedValue2 = 0;
	unsigned char combinedValue3 = 0;
	char arraypanjang[3];
	int combinedValue;
	int j = 0;
    if (!img) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    
    
	unsigned char lsbsem1[8], lsbsem2[8], lsbsem3[8];
	
    for (int i = 0; i < 12; i += 4) {
    	for (int j = 0; j < 4; j++) {
	        unsigned char redLSB = img->data[i + j].red & 1;
	        unsigned char blueLSB = img->data[i + j].blue & 1;
        
	        switch (i / 4) {
	            case 0:
	                lsbsem1[j * 2] = redLSB;
	                lsbsem1[j * 2 + 1] = blueLSB;
	                break;
	            case 1:
	                lsbsem2[j * 2] = redLSB;
	                lsbsem2[j * 2 + 1] = blueLSB;
	                break;
	            case 2:
	                lsbsem3[j * 2] = redLSB;
	                lsbsem3[j * 2 + 1] = blueLSB;
	                break;
	        	}
    	}
	}
		

		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}
		for (int q = 0; q < 8; q++) {
		    combinedValue2 |= lsbsem2[q] << (7 - q);
		}
        for (int q = 0; q < 8; q++) {
		    combinedValue3 |= lsbsem3[q] << (7 - q);
		}
		
		combinedValue1 = combinedValue1 - '0';
		combinedValue2 = combinedValue2 - '0';
		combinedValue3 = combinedValue3 - '0';
		
		if (combinedValue1 != 0 && combinedValue2 != 0 && combinedValue3 != 0) {
			combinedValue = combinedValue1 * 100 + combinedValue2 * 10 + combinedValue3;
		}
		if (combinedValue2 == 0 && combinedValue3 == 0) {
			combinedValue = combinedValue1;
		}
		if (combinedValue1 != 0 && combinedValue2 != 0 && combinedValue3 == 0) {
			combinedValue =  combinedValue1 * 10 + combinedValue2;
		}
    
    return(combinedValue);
}


void extractlsb(const BMPImage *img, int len, int panjang, char hasilLSB[]) {
    if (!img) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    hasilLSB[panjang]; 

    int index = 0;
    

    
	unsigned char lsbsem1[8], lsbsem2[8], lsbsem3[8];
	unsigned char redLSB, blueLSB, redLSB2, blueLSB2, redLSB3, blueLSB3, redLSB4, blueLSB4;
    for (int i = 12; i < len; i+=4) {
    	unsigned char combinedValue1 = 0;
        redLSB = img->data[i].red & 1;
        blueLSB = img->data[i].blue & 1;
        redLSB2 = img->data[i+1].red & 1;
        blueLSB2 = img->data[i+1].blue & 1;
        redLSB3 = img->data[i+2].red & 1;
        blueLSB3 = img->data[i+2].blue & 1;
        redLSB4 = img->data[i+3].red & 1;
		blueLSB4 = img->data[i+3].blue & 1;
		
		lsbsem1[0] = redLSB;
		lsbsem1[1] = blueLSB;
		lsbsem1[2] = redLSB2;
		lsbsem1[3] = blueLSB2;
		lsbsem1[4] = redLSB3;
		lsbsem1[5] = blueLSB3;
		lsbsem1[6] = redLSB4;
		lsbsem1[7] = blueLSB4;
		
		for (int q = 0; q < 8; q++) {
		    combinedValue1 |= lsbsem1[q] << (7 - q);
		}
		hasilLSB[index++] = combinedValue1;
   	}
   	
//		for (int i = 0; i < panjang - 2; i++) {
//        printf("%c", hasilLSB[i]);
//		}
}
