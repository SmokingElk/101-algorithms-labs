#include <iostream>
#include "deque.h"

deque concatenate(const deque& deque1, const deque& deque2) {
    int newSize = deque1.size + deque2.size;
    deque result(newSize);

    for (int i = 0; i < deque1.size; ++i) {
        result.insertBack(deque1.data[(deque1.head + i) % deque1.size]);
    }

    for (int i = 0; i < deque2.size; ++i) {
        result.insertBack(deque2.data[(deque2.head + i) % deque2.size]);
    }

    result.head = 0;
    result.tail = newSize - 1;

    return result;
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

int partition(const deque* d, int low, int high){
    int pivot = d->data[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;
    while (true){
        do {
            i++;
        } while (d->data[i] < pivot);
        do {
            j--;
        } while (d->data[j] > pivot);

        if (i >= j) {
            return j;
        }

        swap(d->data[i], d->data[j]);
    }
}

void quickSort(const deque& d, int low, int high) {
    if (low < high) {
        int pivot = partition(&d, low, high);

        quickSort(d, low, pivot);
        quickSort(d, pivot + 1, high);
    }
}

int main() {
    deque D(5);
    D.insertFront(5);
    D.insertFront(6);
    D.insertBack(7);
    D.insertBack(8);
    D.insertBack(1);

    deque B(5);
    B.insertBack(5);
    B.insertBack(3);
    B.insertBack(7);
    B.insertBack(9);
    B.insertBack(0);

    deque result = concatenate(D, B);
    D.print();
    B.print();
    result.print();
    quickSort(result, 0, result.size-1);
    result.print();

    return 0;
}