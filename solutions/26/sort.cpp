#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#pragma region "Stack"
struct Stack
{
    int length;
    int *data = nullptr;
    int top = -1;

    Stack(int key) : length(10)
    {
        data = new int[10];
        data[++top] = key;
    }

    Stack() : length(10)
    {
        data = new int[10];
    }

    void deleteStack();
    bool isEmptyStack();
    void pushStack(int el);
    void resizeStack(int l = 10);
    void copyStack(Stack &ns);
    int topStack();
    int popStack();
};

void Stack::deleteStack()
{
    delete[] data;
    data = nullptr;
    length = 0;
    top = -1;
}

bool Stack::isEmptyStack()
{
    return (top == -1);
}

void Stack::pushStack(int el)
{
    if (top == length - 1)
    {
        resizeStack();
    }
    data[++top] = el;
}

void Stack::resizeStack(int l)
{
    int *temp = new int[length + l];
    for (int i = 0; i < length; ++i)
    {
        temp[i] = data[i];
    }
    delete[] data;
    data = temp;
    length += l;
}

void Stack::copyStack(Stack &ns)
{
    if (length < ns.length)
    {
        resizeStack(ns.length - length);
    }
    for (int i = 0; i <= ns.top; ++i)
    {
        data[i] = ns.data[i];
    }
    top = ns.top;
}

int Stack::topStack()
{
    if (isEmptyStack())
    {
        throw -2;
    }
    return data[top];
}

int Stack::popStack()
{
    if (isEmptyStack())
    {
        throw -3;
    }
    return data[top--];
}
#pragma endregion

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void quickSort(int arr[], int left, int right) {
    Stack stack;
    stack.pushStack(right);
    stack.pushStack(left);

    while (!stack.isEmptyStack()) {
        int start = stack.topStack();
        stack.popStack();
        int end = stack.topStack();
        stack.popStack();

        if (start >= end) continue;

        int pivot = arr[end];
        int i = start - 1;
        for (int j = start; j < end; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        i++;
        swap(arr[i], arr[end]);
        
        stack.pushStack(end);
        stack.pushStack(i + 1);
        stack.pushStack(i - 1);
        stack.pushStack(start);
    }
}

int main() {
    srand(time(NULL));

    int size = 10;
    int arr[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Исходный массив:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    quickSort(arr, 0, 10 - 1);

    cout << "Отсортированный массив:\n";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
