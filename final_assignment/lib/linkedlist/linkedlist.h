#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdbool.h>

#include "../general/general.h"

typedef struct __Node {
  int key;
  int data;
  struct __Node* next;
} Node;

typedef struct __LinkedList {
  Node* head;

  void (*UpdateOrInsert_Freq)(struct __LinkedList*, int);
  void (*Insert_Distance)(struct __LinkedList*, int, int);
  int (*PopMaxDataWordId_Freq)(struct __LinkedList*, int*);
  int (*PopHead_Distance)(struct __LinkedList*);
} LinkedList;

LinkedList* NewLinkedList();

void LinkedListUpdateOrInsert_Freq(LinkedList*, int);
void LinkedListInsert_Distance(LinkedList*, int, int);
int LinkedListPopMaxDataWordId_Freq(LinkedList*, int*);
int LinkedListPopHead_Distance(LinkedList*);
#endif