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

bool LinkedListInsert(LinkedList* self, int key, void* data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    PrintError("Failed to allocate memory");
    return false;
  }
  newNode->key = key;
  newNode->data = data;

  if (self->head == NULL) {
    self->head = newNode;
    self->tail = newNode;
    return true;
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

  return true;
}

bool LinkedListDelete(LinkedList* self, int key) {
  Node* prev = NULL;
  Node* curr = self->head;

  while (key > curr->key) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      return false;
    }
    if (key == curr->key) {
      prev->next = curr->next;
      free(curr);
      return true;
    }
  }
  return false;
}

bool LinkedListAppend(LinkedList* self, int key, void* data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL) {
    PrintError("Failed to allocate memory");
    return false;
  }
  newNode->key = key;
  newNode->data = data;

  if (self->head == NULL) {
    self->head = newNode;
    self->tail = newNode;
    return true;
  }
  self->tail->next = newNode;
  self->tail = newNode;
  return true;
}