#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <cstring>
#include <stdio.h>
typedef char infotype;
typedef struct node* address;
typedef struct node {
    infotype info;
    address next;
} SLL;

address createNode ();
void mengisiNode (address P, infotype value);
void insertGenap (address *head, infotype arr[]);
void insertAkhir (infotype arr[], address* head, address* tail);
void linkedtoarr(char array[], infotype arr[], address* head, address* tail);


#endif
