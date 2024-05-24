//#include <iostream>
#include <stdio.h>
#include "cip.h"
#include "lsbbmp.h"
#include "display.h"
#include "bmpio.h"
#include "ws.h"
#include "lsbpng.h"
#include "lsbjpeg.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main() {
    int jawab;
    bool valid = false;
    int halaman = 0; 
    Enkripsi En[50];
    utama var[50];
    Dekripsi De[50];
    do{
		displayMenu(&jawab, &valid);    	
		switch (jawab) {
	        case 1:
	        	do {
	        	displayencrypt(&jawab, &valid);
		        	switch (jawab) {
		        		case 1:
		        			encryptBMP(En, var);
		        			main();
		            		break;
		            	case 2:
		            		encryptJPEG(En, var);
		            		main();
		            		break;
						case 3:
							encryptPNG(En, var);
							main();
							break;
		            	case 4:
		            		//whitespace ();
		            		break;
						case 9:
							main();
							break;
						case 0:
							printf("Terima Kasih...");
							exit(0);
		            	default:
		            		printf("Masukkan input yang sesuai. \n\n");
					}	
				} while (true);
	            break;
			case 2 :
				do {
					displaydecrypt(&jawab, &valid);
					switch (jawab) {
		        		case 1:
		        			decryptBMP(En, var, De);
		            		break;
		            	case 2:
		            		decryptJPEG(En, var, De);
		            		break;
						case 3:
							decryptPNG(De, var);
						case 9:
							main();
							break;
						case 0:
							printf("Terima Kasih...");
							exit(0);
		            	default:
		            		printf("Masukkan input yang sesuai. \n\n");
					}
			
				} while (true);
				break;
			case 3:
				
			case 0 :
				printf("Terima Kasih...");	
				exit(0);
			default:
	            printf("Masukkan input yang sesuai. \n\n");
	    }
	} while(true);   
    return 0;
}