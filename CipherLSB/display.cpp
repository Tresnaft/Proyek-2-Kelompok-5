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
    printf("| 1. Enkripsi BMP                                                                               |\n");
    printf("| 2. Dekripsi BMP                                                                               |\n");
    printf("| 3. Enkripsi JPEG                                                                              |\n");
    printf("| 4. Dekripsi JPEG                                                                              |\n");
    printf("| 9. Keluar                                                                                     |\n");
    printf("=================================================================================================\n");
    //printf("display 1");
    printf("Pilihan : ");
    scanf("%d", j);
    //system("cls");
}

void display2 (int *j, Enkripsi *En, utama *var) {
	BMPHeader head;
	BMPImage *bmp;
	char bacafile[100];
    char hasilfile[100];
    int i = 0;
    char message[MAX_MESSAGE_LENGTH];
    char *binaryMessage[MAX_MESSAGE_LENGTH * 8];

    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 0. Kembali                                                                                    |\n");
    printf("=================================================================================================\n");
    printf("=========================================ENKRIPSI================================================\n");
 
    printf("\nMasukan nama file: ");
    scanf("%s", bacafile);
//    strcat(bacafile, ".bmp");

    printf("Masukan nama file setelah disisipkan pesan: "); // pake contoh
    scanf("%s", hasilfile);
//    strcat(hasilfile, ".bmp");
 
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
	//system("pause");
	
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
	printf("berhasil!!\n\n\n");
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
    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 0. Kembali                                                                                    |\n");
    printf("=================================================================================================\n");
    printf("=========================================DEKRIPSI================================================\n");
	
	printf("Masukan nama file: ");
    scanf("%s", hasilfile);
    printf("Masukkan kunci : ");
    scanf("%s", key);

    
    
    printf("%c", key[0]);
    printf("%c", key[1]);
    printf("%c", key[2]);
    printf("%c", key[3]);
    puts("");
    
    matriks_key_LSB(key, keytonum, var);
    
    printf("%d", keytonum[0]);
    printf("%d", keytonum[1]);
    printf("%d", keytonum[2]);
    printf("%d", keytonum[3]);
    puts("");
	
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

    for(int h = 0; h < reallen; h++){
        printf("%d ", num[h]);
    }puts("");

    free(bmp->data);
    free(bmp);
    
    printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, reallen);
    
    for(int l = 0; l < reallen; l++){
        printf("%d ", De->dekripsi[l]);
	}
    
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


    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 0. Kembali                                                                                    |\n");
    printf("=================================================================================================\n");
    printf("=========================================ENKRIPSI================================================\n");
 
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
	//system("pause");
	
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
	
    //char hasil[100];
    char key[4];
    int keytonum[4];
    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 0. Kembali                                                                                    |\n");
    printf("=================================================================================================\n");
    printf("=========================================DEKRIPSI================================================\n");
	
	printf("Masukan nama file: "); // pake contoh
    scanf("%s", hasilfile);
    printf("Masukkan kunci : ");
    scanf("%s", key);
    decode(hasilfile, hasil);
    int batas = strlen(hasil) + 1;
    printf("%d\n", batas);

    
    
    printf("%c", key[0]);
    printf("%c", key[1]);
    printf("%c", key[2]);
    printf("%c", key[3]);
    puts("");
    
    int num[2048];
    matriks_LSB(var, hasil, num, batas);
    
    printf("%d", keytonum[0]);
    printf("%d", keytonum[1]);
    printf("%d", keytonum[2]);
    printf("%d", keytonum[3]);
    puts("");
	
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
