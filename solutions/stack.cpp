#include <iostream>

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

int main()
{
    Stack s1 = Stack(1);
    Stack s2 = Stack(1);
    Stack s3 = Stack(1);

    s1.deleteStack();
    s2.deleteStack();
    s3.deleteStack();

    s1.pushStack(3);
    s1.pushStack(4);
    s1.pushStack(7);

    s3.copyStack(s1);

    Stack perehod = Stack(1);
    perehod.deleteStack();

    while (s1.top != -1)
    {
        int el = s1.popStack();
        perehod.pushStack(el);
    }
    while (perehod.top != -1)
    {
        s2.pushStack(perehod.popStack());
    }
    while (s2.top != -1)
    {
        std::cout << s2.popStack() << " ";
    }
    std::cout << "\n";
    while (s3.top != -1)
    {
        std::cout << s3.popStack() << " ";
    }
}
