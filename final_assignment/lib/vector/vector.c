#include "vector.h"

#include <stdlib.h>

Vector NewVector() {
  Vector newVector;
  newVector.length = 0;
  newVector.capacity = 1;
  newVector.data = (void**)malloc(sizeof(void*) * 1);

  newVector.Push = Push;
  newVector.Pop = Pop;
  newVector.GetDataByIndex = GetDataByIndex;
  newVector.PopDataByIndex = PopDataByIndex;
  newVector.PutDataByIndex = PutDataByIndex;

  return newVector;
}

BOOL Push(void* data, Vector* self) {
  return PutDataByIndex(self->length, data, self);
}

void* Pop(Vector* self) { return PopDataByIndex(self->length, self); }

void* GetDataByIndex(int index, Vector* self) { return self->data[index]; }

void* PopDataByIndex(int index, Vector* self) {
  void* data = self->data[index];
  __DeleteDataByIndex(index, self);
  return data;
}

BOOL PutDataByIndex(int index, void* data, Vector* self) {
  self->length++;
  if (!__AdjustCapacity(INCREASING, self)) {
    return FALSE;
  }
  for (int i = self->length - 1; i > index; --i) {
    self->data[i + 1] = self->data[i];
  }
  self->data[index] = data;

  return TRUE;
}

BOOL __AdjustCapacity(FUNCTION func, Vector* self) {
  if (func == INCREASING) {
    return __EncreaseCapacity(self);
  } else if (func == DECREASING) {
    return __DecreaseCapacity(self);
  }
}

BOOL __EncreaseCapacity(Vector* self) {
  if (self->capacity < self->length) {
    int capacity = self->capacity;

    if (capacity < 8) {
      capacity++;
    } else {
      capacity *= 2;
    }

    self->data = (void**)realloc(self->data, sizeof(void*) * capacity);
    if (self->data == NULL) return FALSE;
    self->capacity = capacity;
  }

  return TRUE;
}

BOOL __DecreaseCapacity(Vector* self) {
  int capacity = self->capacity;
  if (capacity < 8) {
    capacity--;
  } else {
    capacity /= 2;
  }
  capacity < self->length ? self->capacity : capacity;

  if (capacity != self->capacity) {
    self->data = (void**)realloc(self->data, sizeof(void*) * capacity);
    if (self->data == NULL) return FALSE;
    self->capacity = capacity;
  }

  return TRUE;
}

BOOL __DeleteDataByIndex(int index, Vector* self) {
  for (int i = index; i < self->length - 1; ++i) {
    self->data[i] = self->data[i + 1];
  }
  self->length--;
  return !__AdjustCapacity(DECREASING, self);
}