#include "linkedlist.h"

address createNode () {
    address P;
    P = (address) malloc(sizeof(SLL));
    return (P);
}

void mengisiNode (address P, infotype value) {
    P->info = value;
    P->next = NULL;
}


void insertGenap (address *head, infotype arr[]) {
    address pnew;
    address trav = *head;
    
    int len = strlen(arr);

	len = strlen(arr);
    int setlen = len/2;
	for (int i = 0; i < setlen; i ++) {
		pnew = createNode();
		if (pnew == NULL) {
			printf("Alokasi gagal");
			return;
		} else {
			mengisiNode (pnew, arr[setlen + i]);
			pnew->next = trav->next;
			trav->next = pnew;
			
			trav = pnew->next;
//			printf(" %c", pnew->info);
		}
	}
}

void insertAkhir (infotype arr[], address* head, address* tail) {
    address pnew;
    int len = strlen(arr);
    int setlen = len/2;
	for (int i = 0; i < setlen; i ++ ) {
		
	    pnew = createNode();
	    if (pnew == NULL) {
	        printf("Memory penuh");
	    } else {
	        mengisiNode(pnew, arr[i]);
	        if (*head == NULL && *tail == NULL) {
	            *head = pnew;
	        } else {
	            (*tail)->next = pnew;
	        }
	        *tail = pnew;
	    }
//	    printf("%c ", pnew->info);
	}
}


void linkedtoarr(char array[], infotype arr[], address* head, address* tail){
	address awal = *head;
	int i = 0;
	while (awal != NULL) {
		array[i] = awal->info;
		awal = awal->next;
		i++;
	}
	array[i] = '\0';
}
