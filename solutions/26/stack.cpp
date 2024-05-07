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

Stack Concatanate(Stack* a, Stack* b)
{
    Stack c;
    while (!a->isEmptyStack())
    {
        c.pushStack(a->popStack());
    }
    while (!b->isEmptyStack())
    {
        c.pushStack(b->popStack());
    }
    
    return c;
}

int main()
{
    Stack s1;
    s1.pushStack(1);
    s1.pushStack(2);
    s1.pushStack(3);
    s1.pushStack(4);

    Stack s2;
    s1.pushStack(5);
    s2.pushStack(6);
    s2.pushStack(7);
    s2.pushStack(8);
    
    Stack s3 = Concatanate(&s2, &s1);
    while (!s3.isEmptyStack())
    {
        std::cout << s3.popStack() << " ";
    }
}
