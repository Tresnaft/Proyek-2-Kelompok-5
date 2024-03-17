#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "display.h"
#include "lsbbmp.h"
#include "lsbjpeg.h"
#include "cipher.h"
#include "bmpio.h"

void display1 (int *j) {
    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 1. Enkripsi                                                                                   |\n");
    printf("| 2. Dekripsi                                                                                   |\n");
    printf("| 9. Keluar                                                                                     |\n");
    printf("=================================================================================================\n");
    printf("Pilihan : ");
    scanf("%d", j);
    printf("=================================================================================================\n");
    //system("cls");
}
void displayencrypt (int *j) {
    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 1. Enkripsi BMP                                                                               |\n");
    printf("| 2. Enkripsi JPEG 																				|\n");
	printf("| 3. Whitespace Steganography                                                                   |\n");    
    printf("| 9. Keluar                                                                                     |\n");
    printf("=================================================================================================\n");
    printf("Pilihan : ");
    scanf("%d", j);
    printf("=================================================================================================\n");
    system("cls");
}

void displaydecrypt (int *j) {
    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 1. Dekripsi BMP                                                                               |\n");
    printf("| 2. Dekripsi JPEG                                                                              |\n");
    printf("| 9. Keluar                                                                                     |\n");
    printf("=================================================================================================\n");
    printf("Pilihan : ");
    scanf("%d", j);
    printf("=================================================================================================\n");
    system("cls");
}

void display2 (int *j, Enkripsi *En, utama *var) {
	BMPHeader head;
	BMPImage *bmp;
	char bacafile[100];
    char hasilfile[100];
    int i = 0;
    char message[MAX_MESSAGE_LENGTH];
    char *binaryMessage[MAX_MESSAGE_LENGTH * 8];

    printf("|=================================================================================================|\n");
    printf("|=======================================ENKRIPSI BMP==============================================|\n");
    printf("|=================================================================================================|\n");
 
    printf("\nMasukan nama file: ");
    scanf("%s", bacafile);

    printf("Masukan nama file setelah disisipkan pesan: "); // pake contoh
    scanf("%s", hasilfile);
 
    while (getchar() != '\n');
    printf("\nMasukan pesan yang ingin di enkripsi: ");
    fgets(var->pesan, sizeof(var->pesan), stdin);
	var->peslen = strlen(var->pesan);
	if (var->pesan[var->peslen - 1] == '\n') {
	      var->pesan[var->peslen - 1] = '\0';
	      var->peslen--;
	  }
	var->pesan[var->peslen]=var->pesan[var->peslen-1];
	var->isipesan=var->peslen+1;
	var->pesantonum[var->peslen];
	
    printf("Masukan kunci (4 karakter): ");
    scanf("%s", var->kunci);
	puts("");
	/*MENCETAK MATRIKS*/
	printf("=====Matriks Dari Pesan=====\n");
	printf("Pesan : ");

	for(i = 0;i < var->peslen;i++){
	 	printf("%c", var->pesan[i]);	
	} puts("");
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
    puts("");
	printf("=======Proses Input Pesan ke Dalam Gambar==========\n");
    inputMessage(message, En, var);
	*binaryMessage = messageToBinary(message);
	
    bmp = readBMP(bacafile, &head);


    writeMsg(bmp, *binaryMessage);

	writeBMP(hasilfile, bmp, head);
	printf("berhasil!!\n");
	free(bmp->data);
	free(bmp);
}

void display3 (int *j, Enkripsi *En, utama *var, Dekripsi *De) {
	BMPHeader head;
	BMPImage *bmp;
	char hasilfile[100];
	int panjangpesan;
    int reallen;
    char hasil[100];
    char key[4];
    int keytonum[4];
    printf("|=================================================================================================|\n");
    printf("|=========================================DEKRIPSI BMP============================================|\n");
    printf("|=================================================================================================|\n");
	
	printf("Masukan nama file: ");
    scanf("%s", hasilfile);
    printf("Masukkan kunci : ");
    scanf("%s", key);

    
    matriks_key_LSB(key, keytonum, var);
	
	for(int k = 0; k < 4; k++){
		var->kuncitonum[k] = keytonum[k];
	}

	bmp = readBMP(hasilfile, &head);

    panjangpesan = extractinfolen(bmp);

    reallen = panjangpesan;
 
    panjangpesan = panjangpesan * 4 + 8;
	extractlsb(bmp, panjangpesan, reallen, hasil);
	puts("");
	
	int num[2048];
    matriks_LSB(var, hasil, num, reallen);

    free(bmp->data);
    free(bmp);
    
    printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, reallen);

    
    printf("Matriks : \n");
    cetak_matriks_decryptLSB(reallen, De);
    pesan_decryptLSB(De, reallen, var);
    printf("\n=========Pesan Dekripsi==========\n");
    printf("Pesan Dekripsi : ");
    cetak_pesan_decryptLSB(De, reallen);
    puts("");
}

void display4 (int *j, Enkripsi *En, utama *var) {
	char bacafile[100];
    char hasilfile[100];
    int i = 0;


    printf("|=================================================================================================|\n");
    printf("|=======================================ENKRIPSI JPEG=============================================|\n");
    printf("|=================================================================================================|\n");
 
    printf("\nMasukan nama file: ");
    scanf("%s", bacafile);


    printf("Masukan nama file setelah disisipkan pesan: "); 
    scanf("%s", hasilfile);

 
    while (getchar() != '\n');
    printf("\nMasukan pesan yang ingin di enkripsi: ");
    fgets(var->pesan, sizeof(var->pesan), stdin);
	var->peslen = strlen(var->pesan);
	if (var->pesan[var->peslen - 1] == '\n') {
	      var->pesan[var->peslen - 1] = '\0';
	      var->peslen--;
	  }
	var->pesan[var->peslen]=var->pesan[var->peslen-1];
	var->isipesan=var->peslen+1;
	var->pesantonum[var->peslen];
	
    printf("Masukan kunci (4 karakter): ");
    scanf("%s", var->kunci);
	puts("");
	/*MENCETAK MATRIKS*/
	printf("=====Matriks Dari Pesan=====\n");
	printf("Pesan : ");

	for(i = 0;i < var->peslen;i++){
	 	printf("%c", var->pesan[i]);	
	} puts("");
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
    puts("");
	printf("=======Proses Input Pesan ke Dalam Gambar==========\n");
    
	printf("Encoding...\n");
    encode(bacafile, hasilfile, var, En);
}

void display5 (int *j, Enkripsi *En, utama *var, Dekripsi *De) {
	char hasilfile[100];
	char *hasil = (char *)malloc(MAX_MESSAGE_LENGTH + 1);
	
    char key[4];
    int keytonum[4];
    printf("|=================================================================================================|\n");
    printf("|=======================================DEKRIPSI JPEG=============================================|\n");
    printf("|=================================================================================================|\n");
	
	printf("Masukan nama file: "); // pake contoh
    scanf("%s", hasilfile);
    printf("Masukkan kunci : ");
    scanf("%s", key);
    decode(hasilfile, hasil);
    int batas = strlen(hasil);

    
    int num[2048];
    matriks_LSB(var, hasil, num, batas);

	
	printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, batas);
	for(int k = 0; k < 4; k++){
		var->kuncitonum[k] = keytonum[k];
	}
   
    printf("Matriks : \n");
    cetak_matriks_decryptLSB(batas, De);
    pesan_decryptLSB(De, batas, var);
    printf("\n=========Pesan Dekripsi==========\n");
    printf("Pesan Dekripsi : ");
    cetak_pesan_decryptLSB(De, batas);
    puts("");
}

void display6 (int *j){
	WhitespaceSteganography ws_stegano;
    init_stegano();

    char text[100];
    char msg[100];
    
    printf("|=================================================================================================|\n");
    printf("|====================================WHITESPACE STEGANOGRAPHY=====================================|\n");
    printf("|=================================================================================================|\n");
	printf("Masukkan cover message: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Masukkan secret message: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = '\0';

    char *encrypted_text = encrypt(text, msg);
    printf("Cover text: %s\n", encrypted_text);

    char *decrypted_msg = decrypt(encrypted_text);
    printf("Hidden message: %s\n", decrypted_msg);
}
