#include "../general/general.h"

typedef struct __Vector {
  void** data;
  int length;
  int capacity;

  BOOL (*Push)(void*, struct __Vector*);
  void* (*Pop)(struct __Vector*);
  void* (*GetDataByIndex)(int, struct __Vector*);
  void* (*PopDataByIndex)(int, struct __Vector*);
  BOOL (*PutDataByIndex)(int, void*, struct __Vector*);
} Vector;

Vector NewVector();
BOOL Push(void*, Vector*);
void* Pop(Vector*);

void* GetDataByIndex(int, Vector*);
void* PopDataByIndex(int, Vector*);
BOOL PutDataByIndex(int, void*, Vector*);

typedef enum FUNCTION {
  DECREASING,
  INCREASING,
} FUNCTION;

BOOL __AdjustCapacity(FUNCTION, Vector*);
BOOL __EncreaseCapacity(Vector*);
BOOL __DecreaseCapacity(Vector*);

BOOL __DeleteDataByIndex(int, Vector*);