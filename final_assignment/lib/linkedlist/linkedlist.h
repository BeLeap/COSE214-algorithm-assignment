#ifndef LINKEDLIST_H
#define LINKEDLIST_h
#include "../general/general.h"

typedef struct __Node {
  int data;
  struct __Node* next;
} Node;

typedef struct __LinkedList {
  Node* head;
  Node* tail;

  BOOL (*Insert)(struct __LinkedList*, int);
  BOOL (*Delete)(struct __LinkedList*, int);
} LinkedList;

LinkedList NewLinkedList();

BOOL LinkedListInsert(LinkedList*, int);
BOOL LinkedListDelete(LinkedList*, int);
#endif