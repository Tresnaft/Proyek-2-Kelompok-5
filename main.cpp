
//#include <iostream>
#include <stdio.h>
#include "cipher.h"
#include "lsbbmp.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	BMPImage *image;
	utama var[100];
	Enkripsi En[100];
	Dekripsi De[100];
	char message[MAX_MESSAGE_LENGTH];
	char *binaryMessage[MAX_MESSAGE_LENGTH * 8];
	
	printf("Masukkan pesan yang ingin di Enripsi : ");
	fgets(var->pesan, sizeof(var->pesan), stdin);
	var->peslen = strlen(var->pesan);
	if (var->pesan[var->peslen - 1] == '\n') {
	    var->pesan[var->peslen - 1] = '\0';
	    var->peslen--;
	}
	var->pesan[var->peslen]=var->pesan[var->peslen-1];
	var->isipesan=var->peslen+1;
	var->pesantonum[var->peslen];
	
	/*INPUT KUNCI*/
	printf("Masukkan kunci untuk enkripsi (4 karakter) : ");
	scanf("%s", var->kunci);
	puts("");
	/*MENCETAK MATRIKS*/
	printf("=====Matriks Dari Pesan=====\n");
	printf("Pesan : ");
	int i;
	for(i = 0;i < var->peslen;i++){
		printf("%c", var->pesan[i]);	
	}puts("");
	matriks_pesan(var);
	cetak_matriks_pesan(var);
	
	printf("=====Matriks dari kunci=====\n");
	printf("Kunci : %s\n", var->kunci);
	matriks_kunci(var);
	cetak_matriks_kunci(var);
	
	printf("===Matriks dari Pesan Enkripsi===\n");
	Encrypt(En, var);
	cetak_matriks_encrypt(var, En);
	printf("=====Pesan Enkripsi=====");
	pesan_encrypt(En, var);
	printf("\nPesan yang sudah di enkripsi : ");
	cetak_pesan_encrypt(En, var);
	
	// masukan ke gambar
	
	const char *filename_read = "sample.bmp";
    const char *filename_write = "sampleout.bmp";
	inputMessage(message, En);
	
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
	free(image->data);
    free(image);
    
	// membaca gambar
    printf("membaca pesan dari file %s\n", filename_read);
    // Membaca gambar BMP dari file
    image = readBMP(filename_write);
    int panjangpesan;
    int reallen;

    if (!image) {
        fprintf(stderr, "Error reading BMP file\n");
        return 1;
    }

    // Mengambil bit terakhir dari setiap byte dalam komponen warna
    panjangpesan = extractinfolen(image);
    reallen = panjangpesan;
 
    panjangpesan = panjangpesan * 4 + 8;
	extractlsb(image, panjangpesan, reallen);
	
    free(image->data);
    free(image);
    
	
	return 0;
}
