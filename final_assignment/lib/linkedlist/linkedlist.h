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
  int length;

  COMPARE (*Compare)(void*, void*);

  bool (*Insert)(struct __LinkedList*, int, void*);
  void* (*Delete)(struct __LinkedList*, int);
  void* (*Search)(struct __LinkedList*, int);
  int (*GetKeyByIndex)(struct __LinkedList*, int);
  void* (*GetDataByIndex)(struct __LinkedList*, int);
} LinkedList;

LinkedList* NewLinkedList(void*);

bool LinkedListInsert(LinkedList*, int, void*);
void* LinkedListDelete(LinkedList*, int);
void* LinkedListSearch(LinkedList*, int);
int LinkedListGetKeyByIndex(LinkedList*, int);
void* LinkedListGetDataByIndex(LinkedList*, int);
#endif