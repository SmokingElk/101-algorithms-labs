#include <stdio.h>
#include <stdlib.h>

// Структура для представления узла BST
typedef struct NodeBST {
    int d;
    struct NodeBST* l;
    struct NodeBST* r;
} NodeBST;

// Функция для создания нового узла BST
NodeBST* newNodeBST(int data) {
    NodeBST* node = (NodeBST*)malloc(sizeof(NodeBST));
    node->d = data;
    node->l = NULL;
    node->r = NULL;
    return node;
}

NodeBST* minValueNode(NodeBST* node) {
    NodeBST* current = node;
    while (current && current->l != NULL) {
        current = current->l;
    }
    return current;
}

// Рекурсивная функция для удаления узла из бинарного дерева
NodeBST* deleteNodeBST(NodeBST* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->d) {
        root->l = deleteNodeBST(root->l, key);
    } else if (key > root->d) {
        root->r = deleteNodeBST(root->r, key);
    } else {
        // Узел с одним или без дочерних узлов
        if (root->l == NULL) {
            NodeBST* temp = root->r;
            free(root);
            return temp;
        } else if (root->r == NULL) {
            NodeBST* temp = root->l;
            free(root);
            return temp;
        }

        // Узел с двумя дочерними узлами: получаем крайний левый узел в правом поддереве
        NodeBST* temp = minValueNode(root->r);

        // Копируем значение крайнего левого узла в текущий узел
        root->d = temp->d;

        // Удаляем крайний левый узел в правом поддереве
        root->r = deleteNodeBST(root->r, temp->d);
    }
    return root;
}

// Рекурсивная функция для проверки линейности дерева
int isLinearTree(NodeBST* root) {
    if (root == NULL) {
        return 1;
    }
    if (root->l != NULL && root->r != NULL) {
        return 0;
    }
    return isLinearTree(root->l) && isLinearTree(root->r);
}

int main() {
    // Создаем дерево BST
    NodeBST* root = newNodeBST(4);
    root->l = newNodeBST(2);
    root->l->l = newNodeBST(1);
    root->r = newNodeBST(5);
    deleteNodeBST(root, 5);

    // Проверяем, является ли дерево линейным
    if (isLinearTree(root)) {
        printf("The tree is linear.\n");
    } else {
        printf("The tree is not linear.\n");
    }

    return 0;
}