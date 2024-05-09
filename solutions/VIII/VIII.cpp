#include <iostream>

struct Node
{
    int data;
    Node* next;
    Node* prev;
};

Node* createNode(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }

struct List{
    Node* head;
    Node* tail;

    List(): head(nullptr), tail(nullptr){};
    
    void insert(int value) {
        Node* newNode = createNode(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
            newNode->next = newNode; 
            newNode->prev = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev = newNode;
            tail = newNode;
        }
    }

    void remove(Node* node) {
        if (node == head && node == tail) { 
            head = nullptr;
            tail = nullptr;
        } else if (node == head) {
            head = head->next;
            head->prev = tail;
            tail->next = head;
        } else if (node == tail) { 
            tail = tail->prev;
            tail->next = head;
            head->prev = tail;
        } else { 
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        delete node;
    }


    void printList() {
        if (head == nullptr) {
            std::cout << "List is empty" << std::endl;
            return;
        }
        Node* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while (current != head);
        std::cout << std::endl;
    }
};

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void task(List& l){
    Node* current = l.head;
    do {
        swap(current->data, current->next->data);
        current = current->next;
    } while (current != l.head->prev);
}

int main(){
    List L;
    L.insert(5);
    L.insert(6);
    L.insert(8);
    L.insert(0);;
    std::cout << "Current List: ";
    L.printList();
    task(L);
    std::cout << "List before permutations: ";
    L.printList();
}