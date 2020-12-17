#include "vector.h"

#include <stdlib.h>
#include <string.h>

Vector NewVector() {
  Vector newVector;
  newVector.length = 0;
  newVector.capacity = 1;
  newVector.data = (void**)malloc(sizeof(void*) * 1);
  if (newVector.data == NULL) {
    PrintError("Failed to allocated memory");
    return newVector;
  }

  newVector.Push = Push;
  newVector.Pop = Pop;
  newVector.GetDataByIndex = GetDataByIndex;
  newVector.PopDataByIndex = PopDataByIndex;
  newVector.PutDataByIndex = PutDataByIndex;

  return newVector;
}

bool Push(Vector* self, void* data) {
  return PutDataByIndex(self, self->length, data);
}

void* Pop(Vector* self) { return PopDataByIndex(self, self->length - 1); }

void* GetDataByIndex(Vector* self, int index) {
  if (index >= self->length) {
    return NULL;
  }
  return self->data[index];
}

void* PopDataByIndex(Vector* self, int index) {
  if (index >= self->length || index < 0) {
    return NULL;
  }
  void* data = self->data[index];
  __DeleteDataByIndex(self, index);
  return data;
}

bool PutDataByIndex(Vector* self, int index, void* data) {
  self->length++;
  if (index > self->length || index < 0) {
    return false;
  }

  if (!__AdjustCapacity(self, INCREASING)) {
    return false;
  }
  for (int i = self->length - 1; i > index; --i) {
    self->data[i + 1] = self->data[i];
  }
  self->data[index] = data;

  return true;
}

bool __AdjustCapacity(Vector* self, FUNCTION func) {
  if (func == INCREASING) {
    return __EncreaseCapacity(self);
  } else if (func == DECREASING) {
    return __DecreaseCapacity(self);
  }
  return true;
}

bool __EncreaseCapacity(Vector* self) {
  if (self->capacity < self->length) {
    int capacity = self->capacity;

    if (capacity < 8) {
      capacity++;
    } else {
      capacity *= 2;
    }

    self->data = (void**)realloc(self->data, sizeof(void*) * capacity);
    if (self->data == NULL) {
      PrintError("Failed to allocate memory");
      return false;
    }
    self->capacity = capacity;
  }

  return true;
}

bool __DecreaseCapacity(Vector* self) {
  int capacity = self->capacity;
  if (capacity < 8) {
    capacity--;
  } else {
    capacity /= 2;
  }
  capacity = capacity < self->length ? self->capacity : capacity;

  if (capacity != self->capacity) {
    void** temp = (void**)malloc(sizeof(void*) * capacity);
    if (temp == NULL) {
      PrintError("Failed to allocate memory");
      return false;
    }
    memcpy(temp, self->data, sizeof(void*) * self->length);
    free(self->data);
    self->data = temp;
    self->capacity = capacity;
  }

  return true;
}

bool __DeleteDataByIndex(Vector* self, int index) {
  for (int i = index; i < self->length - 1; ++i) {
    self->data[i - 1] = self->data[i];
  }
  self->length--;
  return !__AdjustCapacity(self, DECREASING);
}