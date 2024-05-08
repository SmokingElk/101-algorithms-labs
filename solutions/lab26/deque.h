#pragma once

#include <iostream>
#include <cstdbool>

struct deque {
    int* data;
    int head;
    int tail;
    int size;

    deque(int size) : data(new int[size]), head(-1), tail(0), size(size) {}
    deque() : data(nullptr), head(-1), tail(0), size(0) {}

    ~deque() {
        delete[] data;
    }

    bool isEmpty() {
        return head == -1;
    }

    bool isFull() {
        return (tail + 1) % size == head;
    }

    void insertFront(int value) {
        if (isFull()) {
            std::cout << "Deque is full" << std::endl;
        }
        if (isEmpty()) {
            head = 0;
            tail = 0;
        } else {
            head = (head - 1 + size) % size;
        }
        data[head] = value;
    }

    void insertBack(int value) {
        if (isFull()) {
            std::cout << "Deque is full" << std::endl;
        }
        if (isEmpty()) {
            head = 0;
            tail = 0;
        } else {
            tail = (tail + 1) % size;
        }
        data[tail] = value;
    }

    int deleteFront() {
        if (isEmpty()) {
            std::cout << "Deque is empty" << std::endl;
        }
        int value = data[head];
        if (head == tail) {
            head = -1;
            tail = -1;
        } else {
            head = (head + 1) % size;
        }
        return value;
    }

    int deleteBack() {
        if (isEmpty()) {
            std::cout << "Deque is empty" << std::endl;
        }
        int value = data[tail];
        if (head == tail) {
            head = -1;
            tail = -1;
        } else {
            tail = (tail - 1 + size) % size;
        }
        return value;
    }

    int get_head() {
        if (isEmpty()) {
            std::cout << "Deque is empty" << std::endl;
        }
        return data[head];
    }

    int get_tail() {
        if (isEmpty()) {
            throw "Deque is empty";
        }
        return data[tail];
    }

    void print() {
        if (isEmpty()) {
            std::cout << "Deque is empty" << std::endl;
            return;
        }

        std::cout << "Deque elements: ";
        int current = head;
        while (true) {
            std::cout << data[current] << " ";
            if (current == tail) {
                break;
            }
            current = (current + 1) % size;
        }
        std::cout << std::endl;
    }
};