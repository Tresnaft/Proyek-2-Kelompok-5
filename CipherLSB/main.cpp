//#include <iostream>
#include <stdio.h>
#include "cipher.h"
#include "lsbbmp.h"
#include "display.h"
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
	            display2 (&jawab, En, var);
	            break;
	        case 2:
	            display3 (&jawab, En, var, De);
	            break;
	        case 3:
	            display4 (&jawab, En, var);
	            break;
	        case 4:
	            display5 (&jawab, En, var, De);
	            break;
	    }
	}while(jawab != 9);   
    return 0;
}
