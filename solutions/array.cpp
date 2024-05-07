#include <iostream>

using namespace std;

class Array
{
    int length;
    float *data;
    void copyArray(Array &ar);
    void delArray();

public:
    Array(int length) : length(length)
    {
        try
        {
            data = new float[length];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    Array(Array &ar)
    {
        this->data = new float[ar.length];
        copyArray(ar);
    }
    Array() : data(NULL), length(0) {}
    ~Array()
    {
        delArray();
    }
    int getLength();

    Array &operator=(Array &ar)
    {
        delArray();
        length = ar.getLength();
        data = new float[length];
        copyArray(ar);
        return *this;
    }

    float &operator[](int i)
    {
        return data[i];
    }
};

void Array::copyArray(Array &ar)
{
    for (int i = 0; i < ar.getLength(); i++)
    {
        this->data[i] = ar.data[i];
    }
}

void Array::delArray()
{
    if (this->data != NULL)
    {
        delete[] this->data;
    }
    this->data = NULL;
    this->length = 0;
}

int Array::getLength()
{
    return this->length;
}

int main()
{
    int n;
    cin >> n;
    Array ar(n);
    for (int i = 0; i < ar.getLength(); i++)
    {
        ar[i] = i * i;
    }
    for (int i = 0; i < ar.getLength(); i++)
    {
        cout << ar[i] << " ";
    }
    cout << "\n";
    Array ar2;
    ar2 = ar;
    ar2[0] = 25;
    for (int i = 0; i < ar2.getLength(); i++)
    {
        cout << ar2[i] << " ";
    }
    cout << "\n";
}
