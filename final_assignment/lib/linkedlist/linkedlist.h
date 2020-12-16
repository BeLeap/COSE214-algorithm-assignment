#ifndef LINKEDLIST_H
#define LINKEDLIST_h
#include "../general/general.h"

typedef struct __Node {
  int key;
  void* data;
  struct __Node* next;
} Node;

typedef struct __LinkedList {
  Node* head;
  Node* tail;

  COMPARE (*Compoare)(void*, void*);

  BOOL (*Insert)(struct __LinkedList*, int, void*);
  BOOL (*Delete)(struct __LinkedList*, int);
  BOOL (*Append)(struct __LinkedList*, int, void*);
} LinkedList;

LinkedList* NewLinkedList(void*);

BOOL LinkedListInsert(LinkedList*, int, void*);
BOOL LinkedListDelete(LinkedList*, int);
BOOL LinkedListAppend(LinkedList*, int, void*);
void* LinkedListSearch(LinkedList*, int);
#endif