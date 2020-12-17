#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList* NewLinkedList(void* Compare) {
  LinkedList* newLinkedList = (LinkedList*)malloc(sizeof(LinkedList));
  newLinkedList->head = NULL;
  newLinkedList->tail = NULL;

  newLinkedList->Compare = Compare;

  newLinkedList->Insert = LinkedListInsert;
  newLinkedList->Delete = LinkedListDelete;
  newLinkedList->Append = LinkedListAppend;
  newLinkedList->Search = LinkedListSearch;

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

void* LinkedListDelete(LinkedList* self, int key) {
  Node* prev = NULL;
  Node* curr = self->head;

  if (curr->key == key) {
    self->head = curr->next;
    void* data = curr->data;
    free(curr);
    return data;
  }

  while (key > curr->key) {
    prev = curr;
    curr = curr->next;
    if (curr == NULL) {
      return NULL;
    }
    if (key == curr->key) {
      prev->next = curr->next;
      void* data = curr->data;
      free(curr);
      return data;
    }
  }
  return NULL;
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

void* LinkedListSearch(LinkedList* self, int key) {
  Node* curr = self->head;
  if (curr->key == key) {
    return curr->data;
  } else if (curr->key > key) {
    return NULL;
  }

  while (key > curr->key) {
    curr = curr->next;
    if (curr == NULL) {
      return NULL;
    }
    if (key == curr->key) {
      return curr->data;
    }
  }
  return NULL;
}