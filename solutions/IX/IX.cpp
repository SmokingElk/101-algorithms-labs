#include <iostream>


void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void OddEvenSort(int data[], int n){
    for (int i = 0; i < n; ++i){
        for (int j = (i % 2) ? 0 : 1; j + 1 < n; j += 2){
            if (data[j] > data[j + 1]){
                swap(data[j], data[j + 1]);
            }
        }
    }

}


int main(){
    int n = 10;
    int arr[n];
    for (int i = 0; i < n; ++i){
        arr[i] = rand() % 100;
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    OddEvenSort(arr, n);

    for (int elem : arr){
        std::cout << elem << " ";
    }
    return 0;
}