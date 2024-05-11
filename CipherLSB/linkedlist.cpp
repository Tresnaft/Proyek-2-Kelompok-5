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

void reverseLinkedList(address *head, address *tail) {
    address prevNode = NULL;
    address currentNode = *head;
    address nextNode = NULL;

    *tail = *head; // Menjadikan tail sama dengan head karena setelah proses reverse head akan menjadi tail

    while (currentNode != NULL) {
        // Simpan node berikutnya sebelum diubah
        nextNode = currentNode->next;
        // Ubah pointer next dari node saat ini untuk menunjuk ke node sebelumnya
        currentNode->next = prevNode;
        // Pindahkan pointer prevNode ke currentNode
        prevNode = currentNode;
        // Pindahkan pointer currentNode ke nextNode
        currentNode = nextNode;
    }

    // Ubah head untuk menunjuk ke node terakhir, yang sebelumnya adalah tail
    *head = prevNode;
}

void deleteNode (address *head, address *tail) {
	address pdel;
	address ptemp;
	ptemp = *head;
	while (ptemp != *tail) {
		pdel = ptemp;
		ptemp = ptemp->next;
		free(pdel);
	}
	ptemp->next = NULL;
	*head = NULL;
	*tail = NULL;
	free (*tail);
	free (*head);
}

void linkedtoarr(char array[], address* head, address* tail){
	address awal = *head;
	int i = 0;
	while (awal != NULL) {
		array[i] = awal->info;
		awal = awal->next;
		i++;
	}
	array[i] = '\0';
}

void printAkhir (Dekripsi *De) {
	int panjang = strlen(De->pesanDecrypt);
//	printf("masuk print akhir");
	char kebalik[panjang];
    for (int i = 0; i < panjang; i++) {
        kebalik[i] = De->pesanDecrypt[panjang - i - 1];
    	printf("%c", kebalik[i]);
	}
	
	for (int i = 0; i <= panjang; i++) {
		if (kebalik[i] == '~') {
			kebalik[i] = ' ';
		} 
	}
	
	printf("Plain Text :  ");
	for (int i = 0; i <= panjang-1; i+=2) {
		printf("%c", kebalik[i]); 
	}
	
	for (int i = 1; i <= panjang; i+=2) {
		printf("%c", kebalik[i]); 
	}
	
}

//void proseslinkedlist(){
//	insertAkhir(psn, &first, &last);
//	printf("\n");
//	insertGenap(&first, psn);
//	reverseLinkedList(&first, &last);
//	
//	printf("Bentuk Linked List : ");
//	address awal = first;
//	while (awal != NULL) {
//		printf("| %c | -> ", awal->info);
//		awal = awal->next;
//	}
//	//printf("| %c |", last->next->info);
//	linkedtoarr(var->pesan, &first, &last);
//}
