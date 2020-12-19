#include "heap.h"

#include <stdlib.h>

Heap NewHeap() {
  Heap heap;
  heap.length = 0;
  heap.capacity = 0;
  heap.Insert = HeapInsert;
  return heap;
}

void HeapInsert(Heap* self, int wordId, int freq) {
  self->length++;
  if (self->capacity < self->length) {
    self->capacity *= 2;
    self->elements =
        (HeapNode*)realloc(self->elements, sizeof(HeapNode) * self->capacity);
  }
  self->elements[self->length] ==
}