#include <iostream>
#include <bits/stdc++.h>

struct Queue
{
    int length;
    int *data = NULL;
    int start = 0;
    int depth = 1;

    Queue(int key) : length(10)
    {
        data = new int[10];
        data[0] = key;
    }

    void deleteQueue();
    bool isEmptyQueue();
    void pushQueue(int el);
    void resizeQueue(int l = 10);
    void copyQueue(Queue &nq);
    int topQueue();
    int pullQueue();
};

void Queue::deleteQueue()
{
    if (this->length == 0)
    {
        delete[] this->data;
    }
    this->data = NULL;
    this->depth = 0;
    this->start = 0;
    this->length = 0;
}

bool Queue::isEmptyQueue()
{
    return (this->depth == 0);
}

void Queue::pushQueue(int el)
{
    if (this->depth == this->length)
    {
        this->resizeQueue();
    }
    this->data[this->start + this->depth] = el;
    this->depth += 1;
}

void Queue::resizeQueue(int l)
{
    Queue nq = Queue(this->length + l);
    nq.copyQueue(*this);
    this->deleteQueue();
    *this = nq;
}

void Queue::copyQueue(Queue &q)
{
    if (this->length < q.length)
    {
        this->resizeQueue(q.depth - this->length);
    }
    for (int i = 0; i < q.depth; i++)
    {
        this->data[i] = q.data[q.start + i];
    }
    this->start = 0;
    *this = q;
}

int Queue::topQueue()
{
    if (this->isEmptyQueue())
    {
        throw -2;
    }
    return this->data[this->start];
}

int Queue::pullQueue()
{
    if (this->isEmptyQueue())
    {
        throw -3;
    }
    int el = this->data[this->start];
    this->depth -= 1;
    this->start += 1;
    return el;
}

int main()
{
    Queue q = Queue(5);
    q.pushQueue(2);
    q.pushQueue(7);
    q.pushQueue(3);
    q.pushQueue(1);
    q.pushQueue(-2);
    q.pushQueue(0);
    q.pushQueue(2);
    q.pushQueue(7);
    q.pushQueue(3);
    q.pushQueue(1);
    q.pushQueue(-2);
    q.pushQueue(0);
    q.pushQueue(2);
    q.pushQueue(7);
    q.pushQueue(3);
    q.pushQueue(1);
    q.pushQueue(-2);
    q.pushQueue(0);
    Queue nq = Queue(1);
    nq.copyQueue(q);
    q.deleteQueue();
    std::cout << q.isEmptyQueue() << "\n";
    while (!nq.isEmptyQueue())
    {
        std::cout << nq.pullQueue() << " ";
    }
    return 0;
}
