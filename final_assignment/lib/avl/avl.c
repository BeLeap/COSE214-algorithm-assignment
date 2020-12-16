#include "avl.h"

#include <stdio.h>
#include <stdlib.h>

Node* Insert(Node* root, int key, void* wordList) {
  if (root == NULL) {
    root = (Node*)malloc(sizeof(Node));
    root->key = key;
    root->left = NULL;
    root->right = NULL;
  } else if (key > root->key) {
    root->right = Insert(root->right, key, wordList);
    if (GetBalanceFactor(root) == -2) {
      if (key > root->right->key) {
        root = RR(root);
      } else {
        root = RL(root);
      }
    }
  } else if (key < root->key) {
    root->left = Insert(root->left, key, wordList);
    if (GetBalanceFactor(root) == 2) {
      if (key > root->left->key) {
        root = LL(root);
      } else {
        root = LR(root);
      }
    }
  }

  root->height = GetHeight(root);
  return root;
}

Node* Delete(Node* root, int key) {
  Node* cursor;
  if (root == NULL) {
    return NULL;
  }

  if (key > root->key) {
    root->right = Delete(root->right, key);
    if (GetBalanceFactor(root) == 2) {
      if (GetBalanceFactor(root->left) >= 0) {
        root = RR(root);
      } else {
        root = RL(root);
      }
    }
  } else if (key < root->key) {
    root->left = Delete(root->left, key);
    if (GetBalanceFactor(root) == -2) {
      if (GetBalanceFactor(root->right) <= 0) {
        root = RR(root);
      } else {
        root = RL(root);
      }
    }
  } else {
    if (root->right != NULL) {
      cursor = root->right;
      while (root->left != NULL) root = root->left;

      root->key = cursor->key;
      root->wordList = cursor->wordList;
      root->right = Delete(root->right, cursor->key);

      if (GetBalanceFactor(root) == 2) {
        if (GetBalanceFactor(root->left) >= 0) {
          root = LL(root);
        } else {
          root = LR(root);
        }
      }
    } else {
      return root->left;
    }
  }

  root->height = GetHeight(root);
  return root;
}

int GetHeight(Node* root) {
  int leftHeight, rightHeight;
  if (root == NULL) {
    return 0;
  }

  if (root->left == NULL) {
    leftHeight = 0;
  } else {
    leftHeight = 1 + root->left->height;
  }

  if (root->right == NULL) {
    rightHeight = 0;
  } else {
    rightHeight = 1 + root->right->height;
  }

  return leftHeight > rightHeight ? leftHeight : rightHeight;
}

Node* RotateRight(Node* node) {
  Node* newNode;
  newNode = node->left;
  node->left = newNode->right;
  newNode->right = node;

  node->height = GetHeight(node);
  newNode->height = GetHeight(newNode);
  return newNode;
}

Node* RotateLeft(Node* node) {
  Node* newNode;
  newNode = node->right;
  node->right = newNode->left;
  newNode->left = node;

  node->height = GetHeight(node);
  newNode->height = GetHeight(newNode);
  return newNode;
}

Node* RR(Node* node) {
  node = RotateLeft(node);
  return node;
}

Node* LL(Node* node) {
  node = RotateRight(node);
  return node;
}

Node* LR(Node* node) {
  node->left = RotateLeft(node->left);
  node = RotateRight(node);
  return node;
}

Node* RL(Node* node) {
  node->right = RotateRight(node->right);
  node = RotateLeft(node);
  return node;
}