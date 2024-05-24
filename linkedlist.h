#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include "cip.h"

typedef char infotype;
typedef struct node* address;
typedef struct node {
    infotype info;
    address next;
    address prev;
} SLL;

address createNode();
void mengisiNode(address P, infotype value);
void printList(address head);
void reverseList(address* headRef);
void insertAkhir(infotype arr[], address* head, address* tail, int len);
void moveWord(address *head, address *tail, int steps);
void moveEvenToTail(address *head, address *tail, int len);
void insertGenap(address* head, address* tail, infotype arrnew[]);
void linkedtoarr(char array[], address* head, address* tail);
void dekripLL(utama *var, char psn[], address head, address tail);
void enkripLL(Dekripsi *De, address head, address tail, int reallen);


//
//address createNode ();
//void mengisiNode (address P, infotype value);
//void insertGenap (address *head, infotype arr[]);
//void insertAkhir (infotype arr[], address* head, address* tail);
//void reverseLinkedList(address *head, address *tail);
//void deleteNode (address *head, address *tail);
//void linkedtoarr(char array[], address* head, address* tail);
//void printAkhir (Dekripsi *De);


#endif
