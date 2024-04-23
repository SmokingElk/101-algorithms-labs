#include "BST.h"

BST newBST (float key) {
    BST res = (NodeBST*)malloc(sizeof(NodeBST));

    res->key = key;
    res->left = NULL;
    res->right = NULL;

    return res;
}

bool addToBST (BST *tree, BST node) {
    if (isEmptyBST(*tree)) {
        *tree = node;
        return true;
    } 

    float rootKey = (*tree)->key;

    if (node->key < rootKey) return addToBST(&(*tree)->left, node);
    if (node->key > rootKey) return addToBST(&(*tree)->right, node);

    return false;
}

bool deleteNodeBST (BST *tree, float keyToDelete) {
    if (isEmptyBST(*tree)) return false;

    if ((*tree)->key != keyToDelete) {
        if (keyToDelete < (*tree)->key) return deleteNodeBST(&(*tree)->left, keyToDelete);
        else return deleteNodeBST(&(*tree)->right, keyToDelete);
    }

    if (isLeaf(*tree)) {
        free(*tree);
        *tree = NULL;
        return true;
    } 

    BST old = *tree;

    if (!isEmptyBST(old->left) && isEmptyBST(old->right)) {
        *tree = old->left;
        free(old);
        return true;
    }

    if (isEmptyBST(old->left)) {
        *tree = (*tree)->right;
        free(old);
        return true;
    }

    BST *rightest = &old->left;
    while (!isEmptyBST((*rightest)->right)) rightest = &(*rightest)->right;
    
    old->key = (*rightest)->key;
    BST rightestOld = *rightest;
    *rightest = (*rightest)->left;

    free(rightestOld);
    return true;
}

bool isLeaf (BST tree) {
    if (isEmptyBST) return false;
    return tree->left == NULL && tree->right == NULL;
}

bool isEmptyBST (BST tree) {
    return tree == NULL;
}

BST leftBST (BST root) {
    if (isEmptyBST(root)) return NULL;
    return root->left;
}

BST rightBST (BST root) {
    if (isEmptyBST(root)) return NULL;
    return root->right;
}

float keyRootBST (BST node) {
    return node->key;
}

void deleteBST (BST tree) {
    if (isEmptyBST(tree)) return;

    deleteBST(tree->left);
    deleteBST(tree->right);

    free(tree);
}

void printBST (BST tree, int offset) {
    if (isEmptyBST(tree)) return;

    printBST(tree->right, offset + 1);

    for (int i = 0; i < offset; i++) printf(" ");
    printf("%f\n", tree->key);
    
    printBST(tree->left, offset + 1);
}
