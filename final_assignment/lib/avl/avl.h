#ifndef AVL_H
#define AVL_H
#include "../general/general.h"

typedef struct __Node {
  int key;
  void *wordList;
  struct __Node *left, *right;
  int height;
} AvlNode;

AvlNode *Insert(AvlNode *, int, void *);
AvlNode *Delete(AvlNode *, int);
int GetHeight(AvlNode *);
AvlNode *RotateRight(AvlNode *);
AvlNode *RotateLeft(AvlNode *);
AvlNode *RR(AvlNode *);
AvlNode *LL(AvlNode *);
AvlNode *LR(AvlNode *);
AvlNode *RL(AvlNode *);
int GetBalanceFactor(AvlNode *);
#endif