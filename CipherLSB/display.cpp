#include "display.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void mainMenu (int *j) {
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
    printf("| 2. Enkripsi JPEG                                                                              |\n");
//	printf("| 3. Whitespace Steganography                                                                   |\n");    
    printf("| 9. Keluar                                                                                     |\n");
    printf("=================================================================================================\n");
    printf("Pilihan : ");
    scanf("%d", j);
    printf("=================================================================================================\n");
    //system("cls");
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
    //system("cls");
}

void enkripsiBMP (int *j, Enkripsi *En, utama *var) {
	BMPHeader head;
	BMPImage *bmp;
	address first = NULL;
	address last = NULL;
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

    printf("Masukan nama file setelah disisipkan pesan: "); // pake contoh
    scanf("%s", hasilfile);
 
    while (getchar() != '\n');
    printf("\nMasukan pesan yang ingin di enkripsi: ");
    scanf("%[^\n]s", psn);
	var->peslen = strlen(psn);
	
	if(var->peslen%2 == 1){
    	psn[var->peslen] = ' ';
		var->peslen = var->peslen+1; 	
	}
	for(i = 0;i<var->peslen;i++){
		if(psn[i]==' '){
			psn[i]=var->huruf[0];
		}
	}	

	// Mengacak pesan
	insertAkhir(psn, &first, &last);
	printf("\n");
	insertGenap(&first, psn);
	linkedtoarr(var->pesan, &first, &last);
	printf("ini pesan sebelum reverse %s \n", var->pesan);
	reverseLinkedList(&first, &last);
	
	printf("Bentuk Linked List : ");
	address awal = first;
	while (awal != NULL) {
		printf("| %c | -> ", awal->info);
		awal = awal->next;
	}
	linkedtoarr(var->pesan, &first, &last);
	puts("");
	
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

		
	/*MENCETAK MATRIKS*/
	printf("=====Matriks Dari Pesan=====\n");
	printf("ini%cspasi\n", var->huruf[0]);
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
	printf("ini%cspasi", var->huruf[0]);
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
	
	// printf("isi first %c", first->info);
	// printf("isi last %c", last->info);
	// printf("sebelum del");

	deleteNode(&first, &last);

	// printf("Bentuk Linked List : ");
	// if(first == NULL){
	// 	printf("Linked LIst Kosong");
	// } else {
	// 	printf("isi first %c", last->info);
	// }
}

void dekripsiBMP (int *j, Enkripsi *En, utama *var, Dekripsi *De) {
	BMPHeader head;
	BMPImage *bmp;
	address first = NULL;
	address last = NULL;
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
	extractlsb(bmp, panjangpesan, reallen, hasil);
	puts("");
	
	int num[2048];
	
    matriks_LSB(var, hasil, num, reallen);

    for(int i = 0;i<reallen;i++){
    	printf("Numkey : %d\n", num[i]);	
	}
	
    free(bmp->data);
    free(bmp);
    
    printf("\n===Matriks dari Pesan Dekripsi===");
    Decrypt(var, num, De, reallen);

    
    printf("Matriks : \n");
    cetak_matriks_decryptLSB(reallen, De);
    pesan_decryptLSB(De, reallen, var);

    printf("\n=========Pesan Dekripsi==========\n");
    printf("Pesan Hasil Ekstrak  : ");

    puts("");
    printAkhir (De);
    
}

void enkripsiJPEG (int *j, Enkripsi *En, utama *var) {
	char bacafile[100];
    char hasilfile[100];
    int i = 0;
	address first = NULL, last = NULL;


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
	  
	if (var->peslen % 2 == 1){
		var->pesan[var->peslen]=' ';
	}
	
	for(i = 0;i<var->peslen;i++){
		if(var->pesan[i]==' '){
			var->pesan[i]=var->huruf[0];
		}
	}
	
	var->isipesan=var->peslen+1;
	var->pesantonum[var->peslen];
	
	// Mengacak pesan
	 insertAkhir(var->pesan, &first, &last);
	 printf("\n");
	 insertGenap(&first, var->pesan);
//	 linkedtoarr(var->pesan, &first, &last);
//	 printf("ini pesan sebelum reverse %s \n", var->pesan);
	 reverseLinkedList(&first, &last);
	 linkedtoarr(var->pesan, &first, &last);
	 printf("ini pesan setelah reverse %s \n", var->pesan);
	 
    
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

void dekripsiJPEG (int *j, Enkripsi *En, utama *var, Dekripsi *De) {
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
//    cetak_pesan_decryptLSB(De, batas);
	printAkhir(De);
    puts("");
}

void whitespaceSteganography(int *j) {
    WhitespaceSteganography ws_stegano;
    init_stegano(ws_stegano);

    char text[100];
    char msg[100];

    printf("|=================================================================================================|\n");
    printf("|====================================WHITESPACE STEGANOGRAPHY=====================================|\n");
    printf("|=================================================================================================|\n");
    printf("Masukkan cover message: ");
    fgets(text, sizeof(text), stdin);
    clearInputBuffer();

    printf("Masukkan secret message: ");
    fgets(msg, sizeof(msg), stdin);
    clearInputBuffer();
	printf("PE");
    text[strcspn(text, "\n")] = '\0';
    msg[strcspn(msg, "\n")] = '\0';
//
//    char *encrypted_text = encrypt(text, msg, ws_stegano);
//    printf("Cover text: %s\n", encrypted_text);
//
//    char *decrypted_msg = decrypt(encrypted_text, ws_stegano);
//    printf("Hidden message: %s\n", decrypted_msg);
}
