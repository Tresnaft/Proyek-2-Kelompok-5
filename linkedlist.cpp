#include "linkedlist.h"
#include "cip.h"

address createNode() {
    address P;
    P = (address) malloc(sizeof(SLL));
    return (P);
}

void mengisiNode(address P, infotype value) {
    P->info = value;
    P->next = NULL;
    P->prev = NULL; // Menginisialisasi pointer prev menjadi NULL
}

// Fungsi untuk menampilkan linked list
void printList(address head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    address temp = head;
    
    do {
//        printf("%c ", temp->info);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

// Fungsi untuk membalikkan linked list
void reverseList(address* headRef) {
    if (*headRef == NULL || (*headRef)->next == *headRef) {
        return; // Jika list kosong atau hanya memiliki satu elemen
    }

    address current = *headRef;
    address prev = NULL;
    address next = NULL;
    address head = *headRef;

    // Tukar next dan prev untuk semua node
    do {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    } while (current != head);

    // Perbarui head dan tail
    (*headRef)->next = prev;
    prev->prev = *headRef;
    *headRef = prev;
}

// Fungsi untuk menyisipkan node di akhir linked list
void insertAkhir(infotype arr[], address* head, address* tail, int len) {
    address pnew;
    for (int i = 0; i < len; i++) {
        pnew = createNode();
        if (pnew == NULL) {
            printf("Memory penuh");
            return;
        } else {
            mengisiNode(pnew, arr[i]);
            if (*head == NULL && *tail == NULL) {
                *head = pnew;
                *tail = pnew;
                pnew->next = pnew;
                pnew->prev = pnew;
            } else {
                pnew->prev = *tail; // Menyesuaikan pointer prev node baru
                pnew->next = *head;
                (*tail)->next = pnew;
                (*head)->prev = pnew;
                *tail = pnew;
            }
        }
    }
}

void moveWord(address *head, address *tail, int steps) {
    if (*head == NULL || *tail == NULL) {
        printf("List is empty\n");
        return;
    }

    // Mencari node yang menjadi target untuk dipindahkan
    address current = *head;
    for (int i = 0; i < steps/2; i++) {
        current = current->next;
        if (current == *head) {
//            printf("Invalid step\n");
            return;
        }
    }

    // Mengubah head dan tail menjadi node yang sesuai setelah pemindahan
    *head = current;
    *tail = current->prev;
}

void moveEvenToTail(address *head, address *tail, int len) {
	address temp;
    if (*head == NULL || *tail == NULL) {
        printf("List is empty\n");
        return;
    }

    // Mencari node terakhir yang memiliki nilai genap
    address current = (*head)->next;
    for(int i = 0;i < len/2;i++){
    	temp = current->next->next;
    	current->prev->next = current->next;
    	current->next->prev = current->prev;
    	(*tail)->next = current;
    	current->prev = *tail;
    	*tail = current;
    	current = temp;
	}
	(*tail)->next = *head;
}

void insertGenap(address* head, address* tail, infotype arrnew[]) {
    address pnew;
    address trav = *head;
    int len = strlen(arrnew);
    int half_len = len / 2;
    

    for (int i = 0; i < half_len; i++) {
        pnew = createNode();
        if (pnew == NULL) {
            printf("Alokasi gagal");
            return;
        } else {
            mengisiNode(pnew, arrnew[half_len + i]);
            pnew->next = trav->next;
            pnew->prev = trav;
            trav->next->prev = pnew;
            trav->next = pnew;

            trav = pnew->next;
        }
    }
    *tail = trav->prev;
    (*tail)->next = *head;
}

void linkedtoarr(char array[], address* head, address* tail){
	address awal = *head;
	int i = 0;	
	address temp = *head;
    do {
        array[i] = temp->info;
        temp = temp->next;
        i++;
    } while (temp != *head);
    array[i] = '\0';
}

void dekripLL(utama *var, char psn[], address head, address tail){
	insertAkhir(psn, &head, &tail, var->peslen);
//	printf("Bentuk Linked List : ");
	printList(head);
	for(int i = 0; i < 3; i++){
    	moveWord(&head, &tail, var->peslen);
//	    printf("Linked list setelah di balik :\n");
//	    printList(head);
	    
	    moveEvenToTail(&head, &tail, var->peslen);
//	    printf("Linked list setelah di balik lagi :\n");
//	    printList(head);
	
	    reverseList(&head);
//	    printf("Linked list setelah di-reverse:\n");
//	    printList(head);
	}
	linkedtoarr(var->pesan, &head, &tail);
}

void enkripLL(Dekripsi *De, address head, address tail, int reallen){
	insertAkhir(De->pesanDecrypt, &head, &tail, reallen);
//	printf("Bentuk Linked List : ");
//	printList(head);
	for(int i = 0; i < 3; i++){
	        reverseList(&head);
		    linkedtoarr(De->pesanDecrypt, &head, &tail);
//		    printf("Linked list setelah di-reverse:\n");
//		    printList(head);
		    
		    insertGenap (&head, &tail, De->pesanDecrypt);
//		    printf("Linked list setelah dibagi 2 insert genap:\n");
//		    printList(head);
		    
		    moveWord(&head, &tail, reallen);
//		    printf("Linked list setelah di balik :\n");
//		    printList(head);
	}
	linkedtoarr(De->pesanDecrypt, &head, &tail);
}
