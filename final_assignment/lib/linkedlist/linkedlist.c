#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList* NewLinkedList(void* Compare) {
  LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
  newLinkedList->head = NULL;
  newLinkedList->tail = NULL;

  newLinkedList->Compoare = Compare;

  newLinkedList->Insert = LinkedListInsert;
  newLinkedList->Delete = LinkedListDelete;
  newLinkedList->Append = LinkedListAppend;

  return newLinkedList;
}

BOOL LinkedListInsert(LinkedList* self, int key, void* data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    PrintError("Failed to allocate memory");
    return FALSE;
  }
  newNode->key = key;
  newNode->data = data;

  if (self->head == NULL) {
    self->head = newNode;
    self->tail = newNode;
    return TRUE;
  }

  Node* prev = NULL;
  Node* curr = self->head;
  while (key > curr->key) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      break;
    }
  }

  if (curr == self->head) {
    self->head = newNode;
    newNode->next = curr;
  } else {
    prev->next = newNode;
    newNode->next = curr;
  }

  return TRUE;
}

BOOL LinkedListDelete(LinkedList* self, int key) {
  Node* prev = NULL;
  Node* curr = self->head;

  while (key > curr->key) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      return FALSE;
    }
    if (key == curr->key) {
      prev->next = curr->next;
      free(curr);
      return TRUE;
    }
  }

  return UNKNOWN;
}

BOOL LinkedListAppend(LinkedList* self, int key, void* data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    PrintError("Failed to allocate memory");
    return FALSE;
  }
  newNode->key = key;
  newNode->data = data;

  if (self->head == NULL) {
    self->head = newNode;
    self->tail = newNode;
    return TRUE;
  }
  self->tail->next = newNode;
  self->tail = newNode;
  return TRUE;
}