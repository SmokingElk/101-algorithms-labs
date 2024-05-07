#include <bits/stdc++.h>

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
    std::stack<Node *> getMin();
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
        std::stack<Node *> st = thisKey->getMin();
        Node *min = st.top();
        st.pop();
        int minKey = min->key;
        thisKey->erase(minKey);
        thisKey->key = minKey;

        while (!st.empty())
        {
            Node *pp = st.top();
            pp->updateHeight();
            pp->balance();
            st.pop();
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

std::stack<Node *> Node::getMin()
{
    Node *x = this;
    std::stack<Node *> st;
    st.push(x);
    x = this->right ? this->right : this;
    if (x != this)
        st.push(x);

    while (x->left)
    {
        x = x->left;
        st.push(x);
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
    Pref(&tree);
    std::cout << "\n";

    tree.erase(40);
    tree.erase(50);
    tree.erase(20);
    tree.erase(30);
    tree.erase(80);
    tree.erase(70);
    tree.erase(75);
    tree.erase(76);
    tree.insert(90);
    Pref(&tree);
}
