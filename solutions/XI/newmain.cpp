#include <iostream>
#include <algorithm>
#include <string>

#define MAX_SIZE 100

// Структура для хранения записей в таблице
struct Record
{
    int key;
    std::string data;
};

void shakerSort2(Record table[], int n)
{
    int left = 0, right = n - 1, swapped = 1;
    while (left < right && swapped)
    {
        swapped = 0;
        for (int i = left; i < right; i++)
        {
            if (table[i].key > table[i + 1].key)
            {
                std::swap(table[i], table[i + 1]);
                swapped = 1;
            }
        }
        right--;
        for (int i = right; i > left; i--)
        {
            if (table[i].key < table[i - 1].key)
            {
                std::swap(table[i], table[i - 1]);
                swapped = 1;
            }
        }
        left++;
    }
}

void shakerSort(Record arr[], int n) {
    int left = 0;
    int right = n - 1;
    int swapped = 1;

    while (left < right && swapped) {
        swapped = 0;

        int temp = arr[left].key;
        int swappedIndex = left;
        
        // Проход снизу вверх
        for (int i = left; i <= right; i++) {
            if (arr[i].key < temp) {
                temp = arr[i].key;
                swappedIndex = i;
                swapped = 1;
            }
        }
        if (swapped)
        {
            std::string saveData = arr[swappedIndex].data;
            arr[swappedIndex].key = arr[left].key;
            arr[swappedIndex].data = arr[left].data;
            arr[left].data = saveData;
            arr[left].key = temp;
        }
        left++;

        temp = arr[right].key;
        swappedIndex = right;
        
        // Проход сверху вниз
        for (int i = right; i >= left; i--) {
            if (arr[i].key > temp) {
                temp = arr[i].key;
                swappedIndex = i;
                swapped = 1;
            }
        }
        if (swapped)
        {
            std::string saveData = arr[swappedIndex].data;
            arr[swappedIndex].key = arr[right].key;
            arr[swappedIndex].data = arr[right].data;
            arr[right].data = saveData;
            arr[right].key = temp;
        }
        right--;
    }
}

bool checkDuplicateKeys(Record table[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (table[i].key == table[i + 1].key)
        {
            return true;
        }
    }
    return false;
}

int binarySearch(Record table[], int n, int key)
{
    int left = 0, right = n - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (table[mid].key == key)
        {
            return mid;
        }
        else if (table[mid].key < key)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return -1;
}

void printTable(Record table[], int n)
{
    std::cout << "Таблица:\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << "Ключ: " << table[i].key << ", Запись: " << table[i].data << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    Record table[MAX_SIZE];
    int n;

    std::cout << "Введите количество элементов в таблице: ";
    std::cin >> n;

    std::cout << "Введите ключи и записи для каждого элемента таблицы:\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << "Элемент " << i + 1 << ":\n";
        std::cout << "Ключ: ";
        std::cin >> table[i].key;
        std::cout << "Запись: ";
        std::cin.ignore(); // Очищаем буфер ввода
        std::getline(std::cin, table[i].data);
    }

    std::cout << std::endl;
    printTable(table, n);

    // Проверка наличия повторяющихся ключей
    if (checkDuplicateKeys(table, n))
    {
        std::cout << "Ошибка: таблица содержит повторяющиеся ключи.\n";
        return 1;
    }

    // Таблица до сортировки
    std::cout << "До сортировки:\n";
    printTable(table, n);

    // Сортировка таблицы
    shakerSort(table, n);
    std::cout << "После сортировки:\n";
    printTable(table, n);

    // Двоичный поиск
    int key;
    std::cout << "Введите ключ для поиска: ";
    while (std::cin >> key && key != -1)
    {
        int index = binarySearch(table, n, key);
        if (index != -1)
        {
            std::cout << "Элемент с ключом " << key << " найден: " << table[index].data << std::endl;
        }
        else
        {
            std::cout << "Элемент с ключом " << key << " не найден\n";
        }

        std::cout << "Введите ключ для поиска: ";
    }

    std::cout << "Завершено";

    return 0;
}
