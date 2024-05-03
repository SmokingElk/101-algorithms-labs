#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.h"
#include <iostream>
#include <climits>

using std::cout;
using std::endl;

class BinarySearchTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }
        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void destroyTree(TreeNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void findMinLeaf(TreeNode* node, int& minLeaf) {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {
            if (node->value < minLeaf) minLeaf = node->value;
            return;
        }
        findMinLeaf(node->left, minLeaf);
        findMinLeaf(node->right, minLeaf);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroyTree(root);
    }

    void insert(int value) {
        root = insert(root, value);
    }

    void inorderPrint(TreeNode* node) {
        if (node != nullptr) {
            inorderPrint(node->left);
            std::cout << node->value << " ";
            inorderPrint(node->right);
        }
    }

    void printTree() {
        inorderPrint(root);
        std::cout << std::endl;
    }

    int getMinLeaf() {
        int minLeaf = INT_MAX;
        findMinLeaf(root, minLeaf);
        return minLeaf;
    }
};

#endif // BINARYSEARCHTREE_H
