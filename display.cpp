#include "display.h"


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


void intInput (int *j, bool *valid) {
	*j = -1;
	*valid = false;
	do {
	    if (scanf("%d", j) == true) {
        	*valid = true;
	    } else {
			clearInputBuffer();
		}
	} while (!valid);
}

bool cekSpasi (char namaFile[]) {
	bool ada = false;
	int len = strlen(namaFile);
	int i = 0;
	if (strchr(namaFile, ' ') != NULL) {
		ada = true;
	}
	return ada;
}

void displayMenu (int *j, bool *valid) {
    printf("+=================================================================================================+\n");
    printf("| Pilih opsi dibawah ini:                                                                         |\n");
    printf("| [1]. Enkripsi                                                                                   |\n");
    printf("| [2]. Dekripsi                                                                                   |\n");
    printf("| [0]. Keluar                                                                                     |\n");
    printf("+=================================================================================================+\n");
    printf("| Pilihan : ");
    intInput(j, valid);
    printf("+=================================================================================================+\n");
    system("cls");
}
void displayencrypt (int *j, bool *valid) {
    printf("+=================================================================================================+\n");
    printf("| Pilih opsi dibawah ini:                                                                         |\n");
    printf("| [1]. Enkripsi BMP                                                                               |\n");
    printf("| [2]. Enkripsi JPEG                                                                              |\n");
	printf("| [3]. Enkripsi PNG                                                                               |\n");
    printf("| [4]. Kembali                                                                                    |\n");  
    printf("| [0]. Keluar                                                                                     |\n");
    printf("+=================================================================================================+\n");
    printf("| Pilihan : ");
    intInput(j, valid);
    printf("+=================================================================================================+\n");
    system("cls");
}

void displaydecrypt (int *j, bool *valid) {
    printf("+=================================================================================================+\n");
    printf("| Pilih opsi dibawah ini:                                                                         |\n");
    printf("| [1]. Dekripsi BMP                                                                               |\n");
    printf("| [2]. Dekripsi JPEG                                                                              |\n");
    printf("| [3]. Dekripsi PNG                                                                               |\n");
    printf("| [4]. Kembali                                                                                    |\n");  
    printf("| [0]. Keluar                                                                                     |\n");
    printf("+=================================================================================================+\n");
    printf("| Pilihan : ");
    intInput(j, valid);
    printf("=================================================================================================\n");
    system("cls");
}

void encryptBMP (Enkripsi *En, utama *var) {
	BMPHeader head;
	BMPImage *bmp;
	address first = NULL;
	address tail = NULL;
	char bacafile[100];
    char hasilfile[100];
    char psn[500];
    int psnlen;
    int i = 0;
    bool valid;
    FILE* cekBisa;
    FILE* cekAda;
    int lenkun;
	 
    char message[MAX_MESSAGE_LENGTH];
    char *binaryMessage[MAX_MESSAGE_LENGTH * 8];

    printf("+=================================================================================================+\n");
    printf("|==========================================ENKRIPSI BMP===========================================|\n");
    printf("+=================================================================================================+\n|");
 

    
	valid = false;
	while (!valid) {
		printf("\n| Masukan nama file: ");
    	scanf(" %[^\n]s", bacafile);
		strcat(bacafile, ".bmp");
    	cekAda = fopen(bacafile, "r");
    	
    	if (cekSpasi(bacafile)) {
	        printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else
	    if (cekAda) {
	        fclose(cekAda);
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak ada! Masukan nama file yang sesuai!\n|");
	    }
    }
    
    
    valid = false;
    while (!valid) {
	    printf("\n| Masukan nama file setelah disisipkan pesan: "); 
	    scanf(" %[^\n]s", hasilfile); 
	 	strcat(hasilfile, ".bmp");
		cekBisa = fopen(hasilfile, "w");
		
	    if (cekSpasi(hasilfile)) {
	        	printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else 
		if (cekBisa) {
	        fclose(cekBisa); 
	        remove(hasilfile);
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak bisa dibuat! Masukan nama file yang sesuai!\n|");
	    }
	}


	valid = false;
	while (!valid) {
	    while (getchar() != '\n');
	    printf("| \n| Masukan pesan yang ingin di enkripsi: ");
	    scanf("%[^\n]s", psn);
		
		if (strlen(psn) > 500) {
			printf("| [INFO] Panjang pesan tidak boleh lebih dari 500!\n|");
		} else {
			valid = true;
		}
	}
	puts("");
	
	var->peslen = strlen(psn);
	
	if(var->peslen%2 == 1){
    	psn[var->peslen] = var->huruf[0];
		var->peslen = var->peslen+1; 	
	}
	if(var->peslen%10 == 0){
    	psn[var->peslen] = var->huruf[0];
    	var->peslen = var->peslen+1;
    	psn[var->peslen] = var->huruf[0];
		var->peslen = var->peslen+1; 	
	}
	if(var->peslen%10 == 1){
    	psn[var->peslen] = var->huruf[0];
		var->peslen = var->peslen+1; 	
	}
	
	for(i = 0;i<var->peslen;i++){
		if(psn[i]==' '){
			psn[i]=var->huruf[0];
		}
	}	

	dekripLL(var, psn, first, tail);

	var->isipesan=var->peslen;
	var->pesantonum[var->peslen];
	
	
	do {
	    printf("\n| Masukan kunci (4 huruf): ");
	    scanf("%s", var->kunci);
		puts("");
		lenkun = strlen(var->kunci);
		if (lenkun > 4 || lenkun < 4) {
			printf("| [INFO] Kunci harus memiliki 4 huruf!\n|");
		}	
	} while (lenkun != 4);

		
//	
//	printf("=====Matriks Dari Pesan=====\n");
//	printf("ini%cspasi\n", var->huruf[0]);
//	printf("Pesan : ");

//	for(i = 0;i < var->peslen;i++){
//	 	printf("%c", var->pesan[i]);	
//	} puts("");

	matriks_pesan(var);
//	cetak_matriks_pesan(var);
	
//	printf("=====Matriks dari kunci=====\n");
//	printf("Kunci : %s\n", var->kunci);

	matriks_kunci(var);
	
//	cetak_matriks_kunci(var);
	
//	printf("===Matriks dari Pesan Enkripsi===\n");

	Encrypt(En, var);
	
//	cetak_matriks_encrypt(var, En);
//	printf("=====Pesan Enkripsi=====");

	pesan_encrypt(En, var);

	printf("\n| Pesan yang sudah di enkripsi : ");
	i = 0;
	while(i<var->isipesan){
        printf("%c",En->pesanEncrypt[i]);
        i++;
    }
	
    puts("");
//	printf("=======Proses Input Pesan ke Dalam Gambar==========\n");

    inputMessage(message, En, var);
	*binaryMessage = messageToBinary(message);
	
    bmp = readBMP(bacafile, &head);


    writeMsg(bmp, *binaryMessage);

	writeBMP(hasilfile, bmp, head);
	printf("| Pesan berhasil disisipkan kedalam gambar!\n");
	free(bmp->data);
	free(bmp);
	printf("| \n| ");
	system("pause");
    system("cls");
    
}

void decryptBMP (Enkripsi *En, utama *var, Dekripsi *De) {
	BMPHeader head;
	BMPImage *bmp;
	address first = NULL;
	address tail = NULL;
	char hasilfile[100];
	int panjangpesan;
    int reallen;
    char hasil[100];
    char key[4];
    int keytonum[4];
    bool valid;
    FILE* cekBisa;
    printf("+=================================================================================================+\n");
    printf("|=========================================DEKRIPSI BMP============================================|\n");
    printf("+=================================================================================================+\n|");
	

    valid = false;
    while (!valid) {
	    printf("\n| Masukan nama file: ");
    	scanf(" %[^\n]s", hasilfile);
		strcat(hasilfile, ".bmp");
		cekBisa = fopen(hasilfile, "r");
		
		if (cekSpasi(hasilfile)) {
	        	printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else 
		if (cekBisa) {
	        fclose(cekBisa); 
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak ada! Masukan nama file yang sesuai!\n|");
	    }
	}
    
    
    printf("| Masukkan kunci : ");
    scanf("%s", key);
    
    matriks_key_LSB(key, keytonum, var);
	
	for(int k = 0; k < 4; k++){
		var->kuncitonum[k] = keytonum[k];
	}

	bmp = readBMP(hasilfile, &head);

    panjangpesan = extractinfolen(bmp);

    reallen = panjangpesan;

    panjangpesan = (panjangpesan * 4 + 8)+1;
	printf("| Pesan Hasil Ekstrak LSB : ");
	extractlsb(bmp, panjangpesan, reallen, hasil);
	puts("");
	
	int num[2048];
	
    matriks_LSB(var, hasil, num, reallen);
	
    free(bmp->data);
    free(bmp);
    
//    printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, reallen);

    
//    printf("Matriks : \n");
//    cetak_matriks_decryptLSB(reallen, De);

    pesan_decryptLSB(De, reallen, var);
    
	enkripLL(De, first, tail, reallen);
	
//	printf("\n=========Pesan Dekripsi==========\n");
    printf("| Pesan Hasil Dekripsi  : ");
    for(int k = 0; k < reallen; k++){
		if(De->pesanDecrypt[k]=='~'){
			De->pesanDecrypt[k]=' ';
			}
		printf("%c", De->pesanDecrypt[k]);
	}
    puts(" ");
    printf("\n");
	printf("| \n| ");
    system("pause");
    puts("");
    system("cls");
}

void encryptJPEG (Enkripsi *En, utama *var) {
	char bacafile[100];
    char hasilfile[100];
    int i = 0;
    char psn[500];
    address first = NULL;
	address tail = NULL;
	bool valid;
	FILE *cekAda;
	FILE *cekBisa;
	int lenkun;


    printf("|=================================================================================================|\n");
    printf("|=======================================ENKRIPSI JPEG=============================================|\n");
    printf("|=================================================================================================|\n|");
 
	valid = false;
	while (!valid) {
		printf("\n| Masukan nama file: ");
		scanf(" %[^\n]s", bacafile);
		strcat(bacafile, ".jpeg");
		cekAda = fopen(bacafile, "r");
		
		if (cekSpasi(bacafile)) {
	        printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else
	    if (cekAda) {
	        fclose(cekAda);
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak ada! Masukan nama file yang sesuai!\n|");
	    }
    }
    
    
    valid = false;
    while (!valid) {
	    printf("| Masukan nama file setelah disisipkan pesan: "); 
	    scanf(" %[^\n]s", hasilfile);
	 	strcat(hasilfile, ".jpeg");
	    cekBisa = fopen(hasilfile, "w");
	    
	    if (cekSpasi(hasilfile)) {
	    	printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else 
		if (cekBisa) {
	        fclose(cekBisa); 
	        remove(hasilfile);
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak bisa dibuat! Masukan nama file yang sesuai!\n|");
	    }
	}


	valid = false;
	while (!valid) {
	    while (getchar() != '\n');
	    printf("| \n| Masukan pesan yang ingin di enkripsi: ");
	    scanf("%[^\n]s", psn);
		
		if (strlen(psn) > 500) {
			printf("| [INFO] Panjang pesan tidak boleh lebih dari 500!\n|");
		} else {
			valid = true;
		}
	}
	
	
	var->peslen = strlen(psn);

	if(var->peslen%2 == 1){
    	psn[var->peslen] = var->huruf[0];
		var->peslen = var->peslen+1; 	
	}
	for(i = 0;i<var->peslen;i++){
		if(psn[i]==' '){
			psn[i]=var->huruf[0];
		}
	}
	dekripLL(var, psn, first, tail);
	
	var->isipesan=var->peslen;
	var->pesantonum[var->peslen];
	
	do {
	    printf("\n| Masukan kunci (4 huruf): ");
	    scanf("%s", var->kunci);
		puts("");
		lenkun = strlen(var->kunci);
		if (lenkun > 4 || lenkun < 4) {
			printf("| [INFO] Kunci harus memiliki 4 huruf!\n|");
		}	
	} while (lenkun != 4);
	
//	printf("=====Matriks Dari Pesan=====\n");
//	printf("Pesan : ");
//
//	for(i = 0;i < var->peslen;i++){
//	 	printf("%c", var->pesan[i]);	
//	} puts("");
	matriks_pesan(var);
//	cetak_matriks_pesan(var);
	
//	printf("=====Matriks dari kunci=====\n");
//	printf("Kunci : %s\n", var->kunci);
	matriks_kunci(var);
//	cetak_matriks_kunci(var);
	
//	printf("===Matriks dari Pesan Enkripsi===\n");
	Encrypt(En, var);
//	cetak_matriks_encrypt(var, En);
//	printf("=====Pesan Enkripsi=====");
	pesan_encrypt(En, var);
	printf("\n| Pesan yang sudah di enkripsi : ");
	i = 0;
	while(i<var->isipesan){
        printf("%c",En->pesanEncrypt[i]);
        i++;
    }
    puts("");
//	printf("=======Proses Input Pesan ke Dalam Gambar==========\n");
    
//	printf("Encoding...\n");
    encodeJPEG(bacafile, hasilfile, var, En);
	printf("| Pesan berhasil disisipkan kedalam gambar!\n");
    puts("");
	printf("| \n| ");
    system("pause");
    system("cls");
}

void decryptJPEG (Enkripsi *En, utama *var, Dekripsi *De) {
	char hasilfile[100];
	char *hasil = (char *)malloc(MAX_MESSAGE_LENGTH + 1);
	address first = NULL;
	address tail = NULL;
	bool valid;
	FILE* cekBisa;
	
    char key[4];
    int keytonum[4];
    printf("+=================================================================================================+\n");
    printf("|=======================================DEKRIPSI JPEG=============================================|\n");
    printf("+=================================================================================================+\n|");
	
	valid = false;
    while (!valid) {
	    printf("\n| Masukan nama file: ");
    	scanf(" %[^\n]s", hasilfile);
		strcat(hasilfile, ".jpeg");
		cekBisa = fopen(hasilfile, "r");
		
		if (cekSpasi(hasilfile)) {
	        	printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else 
		if (cekBisa) {
	        fclose(cekBisa); 
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak ada! Masukan nama file yang sesuai!\n|");
	    }
	}
    
    printf("| Masukkan kunci : ");
    scanf("%s", key);
    matriks_key_LSB(key, keytonum, var);
	
	for(int k = 0; k < 4; k++){
		var->kuncitonum[k] = keytonum[k];
	}
    decodeJPEG(hasilfile, hasil);
    int batas = strlen(hasil);

    int num[2048];
    matriks_LSB(var, hasil, num, batas);
	
//	printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, batas);
	
//    printf("Matriks : \n");
//    cetak_matriks_decryptLSB(batas, De);
    pesan_decryptLSB(De, batas, var);
//    printf("\n=========Pesan Dekripsi==========\n");
    enkripLL(De, first, tail, batas);
    printf("| Pesan Dekripsi : ");
    
	for(int k = 0; k < batas; k++){
		if(De->pesanDecrypt[k]=='~'){
			De->pesanDecrypt[k]=' ';
			}
		printf("%c", De->pesanDecrypt[k]);
	}
    puts("");
    printf("\n");
	printf("| \n| ");
    system("pause");
    puts("");
    system("cls");
}

void encryptPNG(Enkripsi *En, utama *var){
	int lenkun;
	FILE* cekAda;
	FILE* cekBisa;
	bool valid;
	char src_image[100], dest_image[100], message[1000], psn[500];
	int i;
	address first = NULL;
	address tail = NULL;
	printf("+=================================================================================================+\n");
    printf("|=========================================ENKRIPSI PNG============================================|\n");
    printf("+=================================================================================================+\n|");

	valid = false;
	while (!valid) {
		printf("\n| Masukan nama file: ");
		scanf(" %[^\n]s", src_image);
		strcat(src_image, ".png");
		cekAda = fopen(src_image, "r");
		
		if (cekSpasi(src_image)) {
	        printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else
	    if (cekAda) {
	        fclose(cekAda);
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak ada! Masukan nama file yang sesuai!\n|");
	    }
    }

    valid = false;
    while (!valid) {
	    printf("| Masukan nama file setelah disisipkan pesan: "); 
	    scanf(" %[^\n]s", dest_image);
	 	strcat(dest_image, ".png");
	    cekBisa = fopen(dest_image, "w");
	    
	    if (cekSpasi(dest_image)) {
	    	printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else 
		if (cekBisa) {
	        fclose(cekBisa); 
	        remove(dest_image);
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak bisa dibuat! Masukan nama file yang sesuai!\n|");
	    }
	}
	
	valid = false;
	while (!valid) {
	    while (getchar() != '\n');
	    printf("| \n| Masukan pesan yang ingin di enkripsi: ");
	    scanf("%[^\n]s", psn);
		
		if (strlen(psn) > 500) {
			printf("| [INFO] Panjang pesan tidak boleh lebih dari 500!\n|");
		} else {
			valid = true;
		}
	}
	
	var->peslen = strlen(psn);

	if(var->peslen%2 == 1){
    	psn[var->peslen] = var->huruf[0];
		var->peslen = var->peslen+1; 	
	}
	for(i = 0;i<var->peslen;i++){
		if(psn[i]==' '){
			psn[i]=var->huruf[0];
		}
	}
	dekripLL(var, psn, first, tail);
	
	var->isipesan=var->peslen;
	var->pesantonum[var->peslen];
	
	do {
	    printf("\n| Masukan kunci (4 huruf): ");
	    scanf("%s", var->kunci);
		puts("");
		lenkun = strlen(var->kunci);
		if (lenkun > 4 || lenkun < 4) {
			printf("| [INFO] Kunci harus memiliki 4 huruf!\n|");
		}	
	} while (lenkun != 4);
	
//	printf("=====Matriks Dari Pesan=====\n");
//	printf("Pesan : ");

	//	for(i = 0;i < var->peslen;i++){
	//	 	printf("%c", var->pesan[i]);	
	//	} puts("");
	matriks_pesan(var);
//	cetak_matriks_pesan(var);
	
//	printf("=====Matriks dari kunci=====\n");
//	printf("Kunci : %s\n", var->kunci);
	matriks_kunci(var);
//	cetak_matriks_kunci(var);
//	
//	printf("===Matriks dari Pesan Enkripsi===\n");
	Encrypt(En, var);
//	cetak_matriks_encrypt(var, En);
//	printf("=====Pesan Enkripsi=====");
	pesan_encrypt(En, var);
	printf("\n| Pesan yang sudah di enkripsi : ");
	i = 0;
	while(i<var->isipesan){
        printf("%c",En->pesanEncrypt[i]);
        i++;
    }
//	printf("\nPesan yang sudah di enkripsi : ");
//	
//	cetak_pesan_encrypt(En, var);
    puts("");


//	printf("Encoding...\n");

	encodePNG(src_image, dest_image, En->pesanEncrypt);
	printf("| Pesan berhasil disisipkan kedalam gambar!\n");
    puts("");
	printf("| \n| ");
    system("pause");
    system("cls");
}

void decryptPNG(Dekripsi *De, utama *var) {
	char src_image[100], key[5], hasil[500];
	address first = NULL;
	address tail = NULL;
	int keytonum[4];
	int num[2048];
	bool valid;
	FILE* cekBisa;
	
	printf("+=================================================================================================+\n");
    printf("|=========================================DEKRIPSI PNG============================================|\n");
    printf("+=================================================================================================+\n|");




	valid = false;
    while (!valid) {
	    printf("\n| Masukan nama file: ");
    	scanf(" %[^\n]s", src_image);
		strcat(src_image, ".png");
		cekBisa = fopen(src_image, "r");
		
		if (cekSpasi(src_image)) {
	        	printf("\n| [INFO] Nama file tidak boleh mengandung spasi!\n|");
		} else 
		if (cekBisa) {
	        fclose(cekBisa); 
	    	valid = true;
	    } else {
	        printf("| [INFO] File tidak ada! Masukan nama file yang sesuai!\n|");
	    }
	}

	printf("| Masukkan kunci : ");
    scanf("%s", key);
	
	decodePNG(src_image, hasil);
	int len = strlen(hasil);

    matriks_key_LSB(key, keytonum, var);
	
	for(int k = 0; k < 4; k++){
		var->kuncitonum[k] = keytonum[k];
	}

    matriks_LSB(var, hasil, num, len);

//    printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, len);

    
//    printf("Matriks : \n");
//    cetak_matriks_decryptLSB(len, De);
    pesan_decryptLSB(De, len, var);
//    printf("\n=========Pesan Dekripsi==========\n");
    enkripLL(De, first, tail, len);
    printf("| Pesan Dekripsi : ");
    
    for(int k = 0; k < len; k++){
		if(De->pesanDecrypt[k]=='~'){
			De->pesanDecrypt[k]=' ';
			}
		printf("%c", De->pesanDecrypt[k]);
	}
	printf("\n");
	printf("\n");
	printf("| \n| ");
	system("pause");
    puts("");
    system("cls");
	
}
