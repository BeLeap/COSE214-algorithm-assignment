#include "../general/general.h"

typedef struct __Vector {
  void** data;
  int length;
  int capacity;

  BOOL (*Push)(struct __Vector*, void*);
  void* (*Pop)(struct __Vector*);
  void* (*GetDataByIndex)(struct __Vector*, int);
  void* (*PopDataByIndex)(struct __Vector*, int);
  BOOL (*PutDataByIndex)(struct __Vector*, int, void*);
} Vector;

#ifndef _HEADER_
#define _HEADER_

Vector NewVector();
BOOL Push(Vector*, void*);
void* Pop(Vector*);

void* GetDataByIndex(Vector*, int);
void* PopDataByIndex(Vector*, int);
BOOL PutDataByIndex(Vector*, int, void*);

typedef enum FUNCTION {
  DECREASING,
  INCREASING,
} FUNCTION;

BOOL __AdjustCapacity(Vector*, FUNCTION);
BOOL __EncreaseCapacity(Vector*);
BOOL __DecreaseCapacity(Vector*);

BOOL __DeleteDataByIndex(Vector*, int);
#endif