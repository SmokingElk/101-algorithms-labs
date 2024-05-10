#include <iostream>


struct Record {
    char * data;
    int key;
};

int binarySearch(Record table[], int n, int key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (table[mid].key == key) {
            return mid;
        } else if (table[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void printTable(Record table[], int n) {
    std::cout << "Table:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Key: " << table[i].key << ", Record: " << table[i].data << std::endl;
    }
    std::cout << std::endl;
}

void swap(int & a, int & b) {
    int temp = a;
    a = b;
    b = temp;
}

void OddEvenSort(Record data[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = (i % 2) ? 0 : 1; j + 1 < n; j += 2) {
            if (data[j].key > data[j + 1].key) {
                swap(data[j].key, data[j + 1].key);
            }
        }
    }

}

int main() {

    Record table[100];
    int n;

    std::cout << "Count elements: ";
    std::cin >> n;

    std::cout << "Press keys:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "Element " << i + 1 << ":\n";
        std::cout << "Key: ";
        std::cin >> table[i].key;
        std::cout << "Record: ";
        std::cin.ignore();
        char * record = new char[100];
        std::cin.getline(record, 100);
        table[i].data = record;
    }

    std::cout << std::endl;
    std::cout << "After Sorted:" << std::endl;
    printTable(table, n);

    OddEvenSort(table, n);
    std::cout << "Before Sorted:" << std::endl;
    printTable(table, n);
    int key;
    std::cout << "Key for search: ";
    while (std::cin >> key && key != -1) {
        int index = binarySearch(table, n, key);
        if (index != -1) {
            std::cout << " Element with key " << key << " found: " << table[index].data << std::endl;
        } else {
            std::cout << "Element with key " << key << " not found\n";
        }

        std::cout << "Press key: ";
    }

    std::cout << "completed";
    return 0;
}