#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct __NodeBST {
    float key;
    struct __NodeBST *left;
    struct __NodeBST *right;
} NodeBST;

typedef NodeBST* BST;

BST newBST (float key);
bool addToBST (BST *tree, BST node);
bool deleteNodeBST (BST *tree, float keyToDelete);
bool isLeaf (BST tree);
bool isEmptyBST (BST tree);
BST leftBST (BST root);
BST rightBST (BST root);
float keyRootBST (BST node);
void deleteBST (BST tree);
void printBST (BST tree, int offset);