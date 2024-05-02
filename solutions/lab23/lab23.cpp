#include <iostream>

using namespace std;

// Структура для представления узла BST
struct NodeBST {
    int d;
    NodeBST* l;
    NodeBST* r;
};

// Функция для создания нового узла BST
NodeBST* newNodeBST(int data) {
    NodeBST* node = new NodeBST;
    node->d = data;
    node->l = nullptr;
    node->r = nullptr;
    return node;
}

NodeBST* minValueNode(NodeBST* node) {
    NodeBST* current = node;
    while (current && current->l != nullptr) {
        current = current->l;
    }
    return current;
}


// Рекурсивная функция для удаления узла из бинарного дерева
NodeBST* deleteNodeBST(NodeBST* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->d) {
        root->l = deleteNodeBST(root->l, key);
    } else if (key > root->d) {
        root->r = deleteNodeBST(root->r, key);
    } else {
        // Узел с одним или без дочерних узлов
        if (root->l == nullptr) {
            NodeBST* temp = root->r;
            delete root;
            return temp;
        } else if (root->r == nullptr) {
            NodeBST* temp = root->l;
            delete root;
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
bool isLinearTree(NodeBST* root) {
    if (root == nullptr) {
        return true;
    }
    if (root->l != nullptr && root->r != nullptr) {
        return false;
    }
    return isLinearTree(root->l) && isLinearTree(root->r);
}


int main() {
    // Создаем дерево BST
    NodeBST* root = newNodeBST(4);
    root->l = newNodeBST(2);
    root->l->l = newNodeBST(1);
    root->r = newNodeBST(4);
    deleteNodeBST(root, 4);

    // Проверяем, является ли дерево линейным
    if (isLinearTree(root)) {
        cout << "The tree is linear." << endl;
    } else {
        cout << "The tree is not linear." << endl;
    }

    return 0;
}