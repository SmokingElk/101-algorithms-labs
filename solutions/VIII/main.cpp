#include <iostream>
#include <string>

using namespace std;

struct Node
{
    string data;
    Node *next;
    Node *prev;
};

class CircularDoublyLinkedList
{
private:
    Node *head;
    int size;

public:
    CircularDoublyLinkedList() : head(nullptr), size(0) {}

    void printList()
    {
        if (head == nullptr)
        {
            cout << "Список пуст" << endl;
            return;
        }
        Node *current = head;
        do
        {
            cout << current->data << " ";
            current = current->next;
        } while (current != head);
        cout << endl;
    }

    void insert(string value)
    {
        Node *newNode = new Node();
        newNode->data = value;
        if (head == nullptr)
        {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else
        {
            Node *lastNode = head->prev;
            lastNode->next = newNode;
            newNode->prev = lastNode;
            newNode->next = head;
            head->prev = newNode;
        }
        size++;
    }

    void remove(string value)
    {
        if (head == nullptr)
        {
            cout << "Список пуст" << endl;
            return;
        }
        Node *current = head;
        while (current->data != value)
        {
            current = current->next;
            if (current == head)
            {
                cout << "Элемент не найден" << endl;
                return;
            }
        }
        Node *prevNode = current->prev;
        Node *nextNode = current->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        if (current == head)
        {
            head = nextNode;
        }
        delete current;
        size--;
    }

    int getSize()
    {
        return size;
    }

    // Lab
    void swapSecondAndSecondLast()
    {
        if (head == nullptr || size < 2)
        {
            cout << "Недостаточно элементов в списке для обмена" << endl;
            return;
        }

        Node *second = head->next;
        Node *secondLast = head->prev->prev;

        if (size == 4)
        {
            secondLast->next->prev = second;
            head->next = secondLast;
            second->next = secondLast->next;
            secondLast->prev = second->prev;
            secondLast->next = second;
            second->prev = secondLast;
            return;
        }

        Node *save1 = second->next;
        Node *save2 = second->prev;

        secondLast->next->prev = second;
        secondLast->prev->next = second;
        second->next = secondLast->next;
        second->prev = secondLast->prev;

        secondLast->next = save1;
        secondLast->prev = save2;
        save1->prev = secondLast;
        save2->next = secondLast;
    }
};

int main()
{
    CircularDoublyLinkedList list;

    list.insert("A");
    list.insert("B");
    list.insert("C");
    list.insert("D");

    cout << "Список после вставки: ";
    list.printList();
    cout << "Список после перестановки: ";
    list.swapSecondAndSecondLast();
    list.printList();
    std::cout << "Длинна:" << list.getSize() << endl;

    list.remove("C");

    cout << "Список после удаления: ";
    list.printList();
    std::cout << "Длинна:" << list.getSize() << endl;

    return 0;
}
