#include <iostream>

#pragma region "Stack"
template <typename T>
struct Stack
{
    int length;
    T *data;
    int top;

    Stack(int key) : length(10), top(-1)
    {
        data = new T[10];
        data[++top] = key;
    }

    Stack() : length(10), top(-1)
    {
        data = new T[10];
    }

    ~Stack()
    {
        delete[] data;
    }

    void deleteStack()
    {
        delete[] data;
        length = 0;
        top = -1;
    }

    bool isEmptyStack()
    {
        return (top == -1);
    }

    void pushStack(T el)
    {
        if (top == length - 1)
        {
            resizeStack();
        }
        data[++top] = el;
    }

    void resizeStack(int l = 10)
    {
        T *temp = new T[length + l];
        for (int i = 0; i < length; ++i)
        {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        length += l;
    }

    void copyStack(Stack<T> &ns)
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

    T topStack()
    {
        if (isEmptyStack())
        {
            throw -2;
        }
        return data[top];
    }

    T popStack()
    {
        if (isEmptyStack())
        {
            throw -3;
        }
        return data[top--];
    }
};

#pragma endregion

struct Node
{
    int key;
    int height;

    Node *right = nullptr;
    Node *left = nullptr;

    Node(int key) : key(key), height(0) {}

    // rotate funcs
    int getHeight();
    void updateHeight();
    int bFactor();
    void balance();
    void leftRotation();
    void rightRotation();

    // base funcs
    void insert(int key);
    Node *find(int key);
    Node *findPrev(int key);
    void erase(int key);
    Stack<Node *> getMin();
    void swap(Node *other);
};

#pragma region rotate funcs
void Node::balance()
{
    if (this->bFactor() == -2)
    {
        if (this->right->bFactor() == 1)
        {
            this->right->rightRotation();
        }
        this->leftRotation();
    }
    else if (this->bFactor() == 2)
    {
        if (this->left->bFactor() == -1)
        {
            this->left->leftRotation();
        }
        this->rightRotation();
    }
}

void Node::leftRotation()
{
    this->swap(this->right);
    Node *save = this->left;
    this->left = this->right;
    this->right = this->left->right;
    this->left->right = this->left->left;
    this->left->left = save;
    this->left->updateHeight();
    this->updateHeight();
}

void Node::rightRotation()
{
    this->swap(this->left);
    Node *save = this->right;
    this->right = this->left;
    this->left = this->right->left;
    this->right->left = this->right->right;
    this->right->right = save;
    this->right->updateHeight();
    this->updateHeight();
}

void Node::updateHeight()
{
    int leftH = (this->left ? this->left->getHeight() + 1 : 0);
    int rightH = (this->right ? this->right->getHeight() + 1 : 0);
    this->height = (leftH > rightH ? leftH : rightH);
}

int Node::getHeight()
{
    return this != nullptr ? this->height : -1;
}

int Node::bFactor()
{
    return this == nullptr ? 0 : this->left->getHeight() - this->right->getHeight();
}
#pragma endregion

#pragma region base funcs
void Node::erase(int key)
{
    Node *prevKey = this->findPrev(key);
    if (!prevKey)
    {
        return;
    }

    Node *thisKey;
    if (prevKey->right && prevKey->right->key == key)
        thisKey = prevKey->right;
    else if (prevKey->left && prevKey->left->key == key)
        thisKey = prevKey->left;
    else
        thisKey = prevKey;

    if (!thisKey->right && !thisKey->left)
    {
        if (prevKey != thisKey)
            (prevKey->right == thisKey ? prevKey->right : prevKey->left) = nullptr;
        else if (prevKey == thisKey && !prevKey->right && !prevKey->left)
        {
            thisKey->key = NULL;
            return;
        }
        delete thisKey;
    }
    else if (thisKey->right || thisKey->left)
    {
        Stack<Node *> st = thisKey->getMin();
        Node *min = st.topStack();
        st.popStack();
        int minKey = min->key;
        thisKey->erase(minKey);
        thisKey->key = minKey;

        while (!st.isEmptyStack())
        {
            Node *pp = st.topStack();
            pp->updateHeight();
            pp->balance();
            st.popStack();
        }
    }
    if (this)
    {
        this->updateHeight();
        this->balance();
    }
}

void Node::swap(Node *other)
{
    int key = this->key;
    this->key = other->key;
    other->key = key;
}

Stack<Node *> Node::getMin()
{
    Node *x = this;
    Stack<Node *> st;
    st.pushStack(x);
    x = this->right ? this->right : this;
    if (x != this)
        st.pushStack(x);

    while (x->left)
    {
        x = x->left;
        st.pushStack(x);
    }

    return st;
}

Node *Node::find(int key)
{
    Node *y = this;
    Node **x = &y;
    while (*x)
    {
        Node *y = *x;
        if (y->key == key)
        {
            *x = y;
            break;
        }

        x = &(key > y->key ? y->right : y->left);
    }

    return *x;
}

Node *Node::findPrev(int key)
{
    Node *y = this;
    Node **x = &y;
    while (*x)
    {
        Node *y = *x;
        if ((y->right && y->right->key == key) ||
            (y->left && y->left->key == key) ||
            (y->key == key))
        {
            *x = y;
            break;
        }

        x = &(key > y->key ? y->right : y->left);
    }

    return *x;
}

void Node::insert(int key)
{
    if (this->key == NULL)
    {
        this->key = key;
        return;
    }
    if (key > this->key)
    {
        if (this->right)
        {
            this->right->insert(key);
        }
        else
        {
            this->right = new Node(key);
            // return this->right;
        }
    }
    else if (key < this->key)
    {
        if (this->left)
        {
            this->left->insert(key);
        }
        else
        {
            this->left = new Node(key);
            // return this->left;
        }
    }
    else
    {
        throw std::runtime_error("This key was inserted before");
    }

    this->updateHeight();
    this->balance();
}
#pragma endregion

#pragma region Out tree in console
void Pref(Node *tree)
{
    if (!tree)
    {
        return;
    }

    std::cout << tree->key << " ";
    Pref(tree->left);
    Pref(tree->right);
}

void Inf(Node *tree)
{
    if (!tree)
    {
        return;
    }

    Inf(tree->left);
    std::cout << tree->key << " ";
    Inf(tree->right);
}

void Post(Node *tree)
{
    if (!tree)
    {
        return;
    }

    Post(tree->left);
    Post(tree->right);
    std::cout << tree->key << " ";
}
#pragma endregion

#pragma region Laba
void UtilsTreeWidth(Node *tree, int *arr, int level)
{
    if (tree)
    {
        arr[level] += 1;
        level += 1;

        UtilsTreeWidth(tree->left, arr, level);
        UtilsTreeWidth(tree->right, arr, level);
    }
}

int TreeWidth(Node *tree)
{
    if (!tree)
    {
        return 0;
    }
    int* arr = new int[100] {0}; // Предполагаем, что высота не больше 100
    UtilsTreeWidth(tree, arr, 0);

    int val = 0;
    int ret = 0;
    for (int i = 0; i < 100; i++)
    {
        if (arr[i] > val)
        {
            val = arr[i];
            ret = i;
        }
    }
    return val;
}

#pragma endregion

int main()
{
    Node tree(20);
    tree.insert(50);
    tree.insert(40);
    tree.insert(30);
    tree.insert(80);
    tree.insert(70);
    tree.insert(75);
    tree.insert(76);
    std::cout << "Дерево в префиксной форме: ";
    Pref(&tree);
    std::cout << "\n";

    // tree.erase(40);
    // tree.erase(50);
    // tree.erase(20);
    // tree.erase(30);
    // tree.erase(80);
    // tree.erase(70);
    // tree.erase(75);
    // tree.erase(76);
    // tree.insert(90);
    // Pref(&tree);
    std::cout << "Максимальная ширина: ";
    std::cout << TreeWidth(&tree);
}
