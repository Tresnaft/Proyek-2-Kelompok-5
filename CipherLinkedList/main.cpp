//#include <iostream>
#include <stdio.h>
#include "cip.h"
#include "lsbbmp.h"
#include "display.h"
#include "bmpio.h"
#include "ws.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int main() {
    int jawab;
    int halaman = 0; 
    Enkripsi En[50];
    utama var[50];
    Dekripsi De[50];
    do{
    	display1 (&jawab);
    	switch (jawab) {
	        case 0:
	            display1 (&jawab);
				break;
	        case 1:
	        	displayencrypt(&jawab);
	        	switch(jawab){
	        		case 0:
	        			display1(&jawab);
	        			break;
	        		case 1:
	        			display2 (&jawab, En, var);
	            		break;
	            	case 2:
	            		display4 (&jawab, En, var);
	            		break;
	            	case 3:
	            		display6 (&jawab);
	            		break;
	            	default:
	            		printf("Masukkan angka 1 atau 2\n\n");
				}
	            break;
			case 2 :
				displaydecrypt(&jawab);
				switch (jawab){
					case 0:
	        			display1(&jawab);
	        			break;
	        		case 1:
	        			display3 (&jawab, En, var, De);
	            		break;
	            	case 2:
	            		display5 (&jawab, En, var, De);
	            		break;
	            	default:
	            		printf("Masukkan angka 1 atau 2\n\n");
				}
				break;
			default:
	            printf("Masukkan angka 1 atau 2\n\n");
	    }
	}while(jawab != 9);   
    return 0;
}
