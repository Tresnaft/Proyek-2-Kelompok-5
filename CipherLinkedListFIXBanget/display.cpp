#include "display.h"


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void displayMenu (int *j) {
    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 1. Enkripsi                                                                                   |\n");
    printf("| 2. Dekripsi                                                                                   |\n");
    printf("| 3. Whitespace Steganography                                                                   |\n"); 
    printf("| 0. Keluar                                                                                     |\n");
    printf("=================================================================================================\n");
    printf("Pilihan : ");
    scanf("%d", j);
    printf("=================================================================================================\n");
    system("cls");
}
void displayencrypt (int *j) {
    printf("=================================================================================================\n");
    printf("| Pilih opsi dibawah ini:                                                                       |\n");
    printf("| 1. Enkripsi BMP                                                                               |\n");
    printf("| 2. Enkripsi JPEG                                                                              |\n");
	printf("| 3. Enkripsi PNG                                                                               |\n");
    printf("| 9. Kembali                                                                                    |\n");  
    printf("| 0. Keluar                                                                                     |\n");
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
    printf("| 3. Dekripsi PNG                                                                               |\n");
    printf("| 9. Kembali                                                                                    |\n");  
    printf("| 0. Keluar                                                                                     |\n");
    printf("=================================================================================================\n");
    printf("Pilihan : ");
    scanf("%d", j);
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
    
    char message[MAX_MESSAGE_LENGTH];
    char *binaryMessage[MAX_MESSAGE_LENGTH * 8];

    printf("|=================================================================================================|\n");
    printf("|=======================================ENKRIPSI BMP==============================================|\n");
    printf("|=================================================================================================|\n");
 
    printf("\nMasukan nama file: ");
    scanf("%s", bacafile);

    printf("Masukan nama file setelah disisipkan pesan: "); 
    scanf("%s", hasilfile);
 
    while (getchar() != '\n');
    printf("\nMasukan pesan yang ingin di enkripsi: ");
    scanf("%[^\n]s", psn);
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
	printf("\n");
	dekripLL(var, psn, first, tail);
	printf("\n");
	var->isipesan=var->peslen;
	var->pesantonum[var->peslen];
	
	int lenkun;
	do{
	    printf("Masukan kunci (4 huruf): ");
	    scanf("%s", var->kunci);
		puts("");
		lenkun = strlen(var->kunci);
		if (lenkun > 4){
			printf("Panjang kunci maksimal 4 huruf !!\n");
		}	
	}while (lenkun != 4);

		
	
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
	i = 0;
	while(i<var->isipesan){
        printf("%c",En->pesanEncrypt[i]);
        i++;
    }
	
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
	printf("\n");
    system("pause");
    puts("");
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

    panjangpesan = (panjangpesan * 4 + 8)+1;
	printf("Pesan Hasil Dekriipsi LSB : ");
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
	printf("Pesan Hasil Dekripsi Hill Cipher : ");
    for(int k = 0; k < reallen; k++){
		printf("%c", De->pesanDecrypt[k]);
	}
    puts("");
    puts("");
    
	enkripLL(De, first, tail, reallen);
	printf("\n=========Pesan Dekripsi==========\n");
    printf("Pesan Hasil Ekstrak  : ");
    for(int k = 0; k < reallen; k++){
		if(De->pesanDecrypt[k]=='~'){
			De->pesanDecrypt[k]=' ';
			}
		printf("%c", De->pesanDecrypt[k]);
	}
    puts(" ");
    printf("\n");
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


    printf("|=================================================================================================|\n");
    printf("|=======================================ENKRIPSI JPEG=============================================|\n");
    printf("|=================================================================================================|\n");
 
    printf("\nMasukan nama file: ");
    scanf("%s", bacafile);


    printf("Masukan nama file setelah disisipkan pesan: "); 
    scanf("%s", hasilfile);

 
    while (getchar() != '\n');
    printf("\nMasukan pesan yang ingin di enkripsi: ");
    scanf("%[^\n]s", psn);
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
	printf("\n");
	dekripLL(var, psn, first, tail);
	printf("\n");
	
	var->isipesan=var->peslen;
	var->pesantonum[var->peslen];
	
    int lenkun;
	do{
	    printf("Masukan kunci (4 huruf): ");
	    scanf("%s", var->kunci);
		puts("");
		lenkun = strlen(var->kunci);
		if (lenkun > 4){
			printf("Panjang kunci maksimal 4 huruf !!\n");
		}	
	}while (lenkun != 4);
	
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
    encodeJPEG(bacafile, hasilfile, var, En);
    printf("\n");
    system("pause");
    puts("");
    system("cls");
}

void decryptJPEG (Enkripsi *En, utama *var, Dekripsi *De) {
	char hasilfile[100];
	char *hasil = (char *)malloc(MAX_MESSAGE_LENGTH + 1);
	address first = NULL;
	address tail = NULL;
	
    char key[4];
    int keytonum[4];
    printf("|=================================================================================================|\n");
    printf("|=======================================DEKRIPSI JPEG=============================================|\n");
    printf("|=================================================================================================|\n");
	
	printf("Masukan nama file: "); 
    scanf("%s", hasilfile);
    printf("Masukkan kunci : ");
    scanf("%s", key);
    matriks_key_LSB(key, keytonum, var);
	
	for(int k = 0; k < 4; k++){
		var->kuncitonum[k] = keytonum[k];
	}
    decodeJPEG(hasilfile, hasil);
    int batas = strlen(hasil);

    int num[2048];
    matriks_LSB(var, hasil, num, batas);
	
	printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, batas);
	
    printf("Matriks : \n");
    cetak_matriks_decryptLSB(batas, De);
    pesan_decryptLSB(De, batas, var);
	printf("Pesan Hasil Dekripsi Hill Cipher : ");
    for(int k = 0; k < batas; k++){
		printf("%c", De->pesanDecrypt[k]);
	}
    puts("");
    puts("");
    printf("\n=========Pesan Dekripsi==========\n");
    enkripLL(De, first, tail, batas);
    printf("Pesan Dekripsi : ");
    
	for(int k = 0; k < batas; k++){
		if(De->pesanDecrypt[k]=='~'){
			De->pesanDecrypt[k]=' ';
			}
		printf("%c", De->pesanDecrypt[k]);
	}
    puts("");
    printf("\n");
    system("pause");
    puts("");
    system("cls");
}

void encryptPNG(Enkripsi *En, utama *var){
	printf("|=================================================================================================|\n");
    printf("|=========================================ENKRIPSI PNG============================================|\n");
    printf("|=================================================================================================|\n");

	char src_image[100], dest_image[100], message[1000], psn[500];
	int i;
	address first = NULL;
	address tail = NULL;

	printf("Enter Source Image Path: ");
	scanf("%s", src_image);

	printf("Enter Message to Hide: ");
	scanf("%[^\n]s", psn);
	getchar(); 
    scanf("%[^\n]s", psn);
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
	printf("\n");
	dekripLL(var, psn, first, tail);
	printf("\n");
	var->isipesan=var->peslen;
	var->pesantonum[var->peslen];
	
    int lenkun;
	do{
	    printf("Masukan kunci (4 huruf): ");
	    scanf("%s", var->kunci);
		puts("");
		lenkun = strlen(var->kunci);
		if (lenkun > 4){
			printf("Panjang kunci maksimal 4 huruf !!\n");
		}	
	}while (lenkun != 4);
	
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

	printf("Enter Destination Image Path: ");
	scanf("%s", dest_image);

	printf("Encoding...\n");

	encodePNG(src_image, dest_image, En->pesanEncrypt);
	printf("\n");
    system("pause");
    puts("");
    system("cls");
}

void decryptPNG(Dekripsi *De, utama *var){
	printf("|=================================================================================================|\n");
    printf("|=========================================DEKRIPSI PNG============================================|\n");
    printf("|=================================================================================================|\n");

	char src_image[100], key[5], hasil[500];
	address first = NULL;
	address tail = NULL;
	int keytonum[4];
	int num[2048];


	printf("Enter Source Image Path: ");
	scanf("%s", src_image);

	printf("Decoding...\n");
	decodePNG(src_image, hasil);
	int len = strlen(hasil);

	printf("Masukkan kunci : ");
    scanf("%s", key);
    matriks_key_LSB(key, keytonum, var);
	
	for(int k = 0; k < 4; k++){
		var->kuncitonum[k] = keytonum[k];
	}

    matriks_LSB(var, hasil, num, len);

    printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, len);

    
    printf("Matriks : \n");
    cetak_matriks_decryptLSB(len, De);
    pesan_decryptLSB(De, len, var);
    printf("Pesan Hasil Dekripsi Hill Cipher : ");
    for(int k = 0; k < len; k++){
		printf("%c", De->pesanDecrypt[k]);
	}
    puts("");
    puts("");
    printf("\n=========Pesan Dekripsi==========\n");
    enkripLL(De, first, tail, len);
    printf("Pesan Dekripsi : ");
    
    for(int k = 0; k < len; k++){
		if(De->pesanDecrypt[k]=='~'){
			De->pesanDecrypt[k]=' ';
			}
		printf("%c", De->pesanDecrypt[k]);
	}
	printf("\n");
	printf("\n");
	system("pause");
    puts("");
    system("cls");
	
}