#ifndef LINKEDLIST_H
#define LINKEDLIST_h
#include <stdbool.h>

#include "../general/general.h"

typedef struct __Node {
  int key;
  void* data;
  struct __Node* next;
} Node;

typedef struct __LinkedList {
  Node* head;
  Node* tail;

  COMPARE (*Compare)(void*, void*);

  bool (*Insert)(struct __LinkedList*, int, void*);
  bool (*Delete)(struct __LinkedList*, int);
  bool (*Append)(struct __LinkedList*, int, void*);
} LinkedList;

LinkedList* NewLinkedList(void*);

bool LinkedListInsert(LinkedList*, int, void*);
bool LinkedListDelete(LinkedList*, int);
bool LinkedListAppend(LinkedList*, int, void*);
void* LinkedListSearch(LinkedList*, int);
#endif