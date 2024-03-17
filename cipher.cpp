#include <stdio.h>
#include "cipher.h"
#include <cstring>
#include "bmpio.h"

void cetak_pesan_encrypt(Enkripsi *En, utama *var){
	int i=0;
    while(i<var->isipesan-1){
        printf("%c",En->pesanEncrypt[i]);
        i++;
    }
}

void cetak_matriks_encrypt(utama *var, Enkripsi *En){
	int i,j;
	//if(batas%2==0){
		for(i = 0;i < 3; i++){
			for(j = 0; j < var->peslen; j++){
				if(i==0 && j%2==0){
					printf("%d\t", En->enkripsi[j]);
				}else if(i==1 && j%2!=0){
					printf("%d\t", En->enkripsi[j]);
				}
			}printf("\n");
		}
}

void cetak_pesan_decrypt(Dekripsi *De, utama *var){
	int i=0;
    while(i<var->isipesan-1){
        printf("%c",De->pesanDecrypt[i]);
        i++;
    }
}

void cetak_pesan_decryptLSB(Dekripsi *De, int batas){
	int i=0;
    while(i<batas){
        printf("%c",De->pesanDecrypt[i]);
        i++;
    }
}

void cetak_matriks_decrypt(utama *var, Dekripsi *De){
	int i,j;
	//if(batas%2==0){
		for(i = 0;i < 3; i++){
			for(j = 0; j < var->peslen; j++){
				if(i==0 && j%2==0){
					printf("%d\t", De->dekripsi[j]);
				}else if(i==1 && j%2!=0){
					printf("%d\t", De->dekripsi[j]);
				}
			}printf("\n");
		}
}

void cetak_matriks_decryptLSB(int batas, Dekripsi *De){
	int i,j;
	//if(batas%2==0){
		for(i = 0;i < 3; i++){
			for(j = 0; j < batas-2; j++){
				if(i==0 && j%2==0){
					printf("%d\t", De->dekripsi[j]);
				}else if(i==1 && j%2!=0){
					printf("%d\t", De->dekripsi[j]);
				}
			}printf("\n");
		}
}


void pesan_encrypt(Enkripsi *En, utama *var){
	int i = 0, j;
	while(i < var->isipesan){
		for(j = 0;j <= 79;j++){
			if(En->enkripsi[i]==j){
				En->pesanEncrypt[i]=var->karakter[j];
			}
		}
		i++;
	}
}

void pesan_decrypt(Dekripsi *De, utama *var){
	int i = 0, j;
	while(i < var->isipesan){
		for(j = 0;j <= 79;j++){
			if(De->dekripsi[i]==j){
				De->pesanDecrypt[i]=var->karakter[j];
			}
		}
		i++;
	}
}

void pesan_decryptLSB(Dekripsi *De, int batas, utama *var){
	int i = 0, j;
	while(i < batas-2){
		for(j = 0;j <= 79;j++){
			if(De->dekripsi[i]==j){
				De->pesanDecrypt[i]=var->karakter[j];
			}
		}
		i++;
	}
}


void matriks_pesan(utama *var){
	int i,j;
	for(i = 0;i<var->isipesan;i++){
		for(j = 0;j < 79;j++){
			if(var->pesan[i]==var->karakter[j]){
				var->pesantonum[i]=j;
			}
		}
	}
}

void matriks_LSB(utama *var, char hasilLSB[], int numLSB[], int batas){
	int i,j;
	for(i = 0;i<batas;i++){
		for(j = 0;j < 79;j++){
			if(hasilLSB[i]==var->karakter[j]){
				numLSB[i]=j;
			}
		}
	}
}

void matriks_kunci(utama *var){
	int i,j;
	for(i = 0;i < 4;i++){
		for(j = 0;j < 79;j++){
			if(var->kunci[i]==var->karakter[j]){
				var->kuncitonum[i]=j;
			}
		}
	}
}

void matriks_key_LSB(char key[], int keytonum[], utama *var){
	int i,j;
	for(i = 0;i < 4;i++){
		for(j = 0;j < 79;j++){
			if(key[i]==var->karakter[j]){
				keytonum[i]=j;
			}
		}
	}
}

void cetak_matriks_pesan(utama *var){
	int i,j;
	//if(batas%2==0){
		for(i = 0;i < 3; i++){
			for(j = 0; j < var->isipesan - 1; j++){
				if(i==0 && j%2==0){
					printf("%d\t", var->pesantonum[j]);
				}else if(i==1 && j%2!=0){
					printf("%d\t", var->pesantonum[j]);
				}
			}printf("\n");
		}
}

void cetak_matriks_kunci(utama *var){
	int i,j;
	//if(batas%2==0){
		for(i = 0;i < 3; i++){
			for(j = 0; j < 4; j++){
				if(i==0 && j%2==0){
					printf("%d\t", var->kuncitonum[j]);
				}else if(i==1 && j%2!=0){
					printf("%d\t", var->kuncitonum[j]);
				}
			}printf("\n");
		}
}

void Encrypt(Enkripsi *En, utama *var){
	int i,j=0;
	En->enkripsi[var->isipesan];
		for(i = 0;i < var->isipesan; i+=2){
			En->enkripsi[j] = ((var->kuncitonum[0]*var->pesantonum[i])+(var->kuncitonum[2]*var->pesantonum[i+1]))%79;
			En->enkripsi[j+1] = ((var->kuncitonum[1]*var->pesantonum[i])+(var->kuncitonum[3]*var->pesantonum[i+1]))%79;
			j+=2;
		}
}

/*======================================Dekripsi=============================*/
int determinan(int kunci[]){
	return (kunci[0]*kunci[3])-(kunci[1]*kunci[2]);
}

void invers_matriks(int kunci[], int invers[]){
	int temp,i;
    temp=kunci[3];
    kunci[3]=kunci[0];
    kunci[0]=temp;
    kunci[1]*=-1;
    kunci[2]*=-1;
    for(i=0;i<4;i++){
        invers[i]=kunci[i];
    }
}

int Zinv(int angka){
	int i,j;
    for (i=1;i<79;i++){
        for (j=1;j<79;j++){
            if ((i*j)%79==1){
               if(i==angka){
                   return j;
               }
            }
        }
    }
    return 0;
}

int modulus(int angka){
	int hasil;
    if(angka<0 && angka>=-79){
        hasil=angka+79;
    }
    else if(angka<-79){
        while(angka<0){;
            angka+=79;
        }
        hasil=angka;
    }
    else{
        hasil=angka%79;
    }
    return hasil;
}


void Decrypt(utama *var, int numLSB[], Dekripsi *De, int batas) {
	int Z,i,j;
    int inversZ;
    int inv[4],invkey[4],modkey[4];
    int hasil[batas];
    int det;
    Z=modulus(determinan(var->kuncitonum));
    puts("");
    inversZ = Zinv(Z);
      
    invers_matriks(var->kuncitonum,inv);
    for(i=0;i<4;i++){
        invkey[i]=inversZ*inv[i];
        modkey[i]=modulus(invkey[i]);
    }
    
    
    j=0;
    for(i=0;i<batas;i+=2){
        hasil[j]=((modkey[0]*numLSB[i])+(modkey[2]*numLSB[i+1]));
        hasil[j+1]=((modkey[1]*numLSB[i])+(modkey[3]*numLSB[i+1]));
        j+=2;
    }
    
    for(i=0;i<batas;i++){
        De->dekripsi[i]=modulus(hasil[i]);
    }
}
