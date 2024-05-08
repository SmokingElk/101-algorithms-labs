#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* prev;
};

struct List {
    Node* head;
    Node* tail;
};

Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    return newNode;
}

void initList(List& list) {
    list.head = createNode(0);
    list.tail = createNode(0);
    list.head->next = list.tail;
    list.tail->prev = list.head;
}

void append(List& list, int value) {
    Node* newNode = createNode(value);
    Node* last = list.tail->prev;
    last->next = newNode;
    newNode->prev = last;
    newNode->next = list.tail;
    list.tail->prev = newNode;
}

void printList(const List& list) {
    Node* current = list.head->next;
    while (current != list.tail) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int length(const List& list) {
    int count = 0;
    Node* current = list.head->next;
    while (current != list.tail) {
        count++;
        current = current->next;
    }
    return count;
}

void task(List& list, int value, int k) {
    int currentLength = length(list);
    if (currentLength >= k) return;

    for (int i = currentLength; i < k; ++i) {
        append(list, value);
    }
}

void remove(List& list, Node* node) {
    if (node == list.head || node == list.tail) return;

    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
}

int main() {
    List myList;
    initList(myList);

    append(myList, 10);
    append(myList, 20);
    append(myList, 30);

    task(myList, 0, 5);

    printList(myList);

    remove(myList, myList.head->next);

    printList(myList);

    return 0;
}