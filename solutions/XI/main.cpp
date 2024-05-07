#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shakerSort(int arr[], int n) {
    int left = 0;
    int right = n - 1;
    int swapped = 1;

    while (left < right && swapped) {
        swapped = 0;

        int temp = arr[left];
        int swappedIndex = left;
        
        // Проход снизу вверх
        for (int i = left; i <= right; i++) {
            if (arr[i] < temp) {
                temp = arr[i];
                swappedIndex = i;
                swapped = 1;
            }
        }
        if (swapped)
        {
            arr[swappedIndex] = arr[left];
            arr[left] = temp;
        }
        left++;

        temp = arr[right];
        swappedIndex = right;
        
        // Проход сверху вниз
        for (int i = right; i >= left; i--) {
            if (arr[i] > temp) {
                temp = arr[i];
                swappedIndex = i;
                swapped = 1;
            }
        }
        if (swapped)
        {
            arr[swappedIndex] = arr[right];
            arr[right] = temp;
        }
        right--;
    }
}


int main() {
    srand(time(NULL));
    int n = 15;
    int arr[n];

    printf("Исходный массив:\n");
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
        printf("%d ", arr[i]);
    }
    printf("\n");

    shakerSort(arr, n);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
