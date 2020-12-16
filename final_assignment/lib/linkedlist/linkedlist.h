#ifndef _LINKEDLISTH_
#define _LINKEDLISTH_

#include "../general/general.h"

typedef struct __Node {
  void* data;
  struct __Node* next;
} Node;

typedef struct __LinkedList {
  Node* head;
  Node* tail;

  BOOL (*Insert)(void*);
  BOOL (*Delete)(void*);
} LinkedList;

LinkedList NewLinkedList();

BOOL Insert(void* data);
BOOL Delete(void* data);

#endif