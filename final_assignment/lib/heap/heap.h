#ifndef HEAP_H
#define HEAP_H

typedef struct __HeapNode {
  int wordId;
  int freq;
} HeapNode;

typedef struct __Heap {
  HeapNode* elements;
  int length;
  int capacity;

  void (*Insert)(struct __Heap*, int, int);
} Heap;

Heap NewHeap();

void HeapInsert(Heap*, int, int);

#endif