#ifndef _LINKEDLISTH_
#define _LINKEDLISTH_

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

BOOL Insert(LinkedList*, int);
BOOL Delete(LinkedList*, int);

#endif