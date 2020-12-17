#ifndef VECTOR_H
#define VECTOR_H
#include <stdbool.h>

#include "../general/general.h"

typedef struct __Vector {
  void** data;
  int length;
  int capacity;

  bool (*Push)(struct __Vector*, void*);
  void* (*Pop)(struct __Vector*);
  void* (*GetDataByIndex)(struct __Vector*, int);
  void* (*PopDataByIndex)(struct __Vector*, int);
  bool (*PutDataByIndex)(struct __Vector*, int, void*);
} Vector;

Vector NewVector();
bool Push(Vector*, void*);
void* Pop(Vector*);

void* GetDataByIndex(Vector*, int);
void* PopDataByIndex(Vector*, int);
bool PutDataByIndex(Vector*, int, void*);

typedef enum FUNCTION {
  DECREASING,
  INCREASING,
} FUNCTION;

bool __AdjustCapacity(Vector*, FUNCTION);
bool __EncreaseCapacity(Vector*);
bool __DecreaseCapacity(Vector*);

bool __DeleteDataByIndex(Vector*, int);
#endif