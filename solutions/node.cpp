#include <iostream>

using namespace std;

class Node
{
    int val;
    Node *next;

    void NodeInit(int val)
    {
        this->val = val;
        this->next = nullptr;
    }

    void DeleteNode()
    {
        this->val = NULL;
        this->next = nullptr;
    }

    void PrintNode()
    {
        if (isEmpty() || !val){
            return;
        }
        cout << this->val << " ";

    }

public:
    Node(int el)
    {
        NodeInit(el);
    }

    Node()
    {
        NodeInit(NULL);
    }

    ~Node()
    {
        DeleteNode();
    }

    bool operator== (Node b)
    {
        return (val == b.val && next == b.next);
    }

    Node &operator= (Node &node)
    {
        DeleteNode();
        NodeInit(node.val);
        next = node.next;
        return *this;
    }

    bool operator!= (Node b)
    {
        return (val != b.val || next != b.next);
    }

    int &operator[] (int i)
    {
        Node *node = this;
        while (i != 0)
        {
            i -= 1;
            node = node->next;
            if (!node)
            {
                throw -1;
            }
        }
        return node->val;
    }

    bool isEmpty()
    {
        return this == nullptr;
    }
    int getVal()
    {
        return val;
    }

    void PrintList()
    {
        Node * p = this;
        while(!p->isEmpty()){
            p->PrintNode();
            p = p->next;
        }
        cout << "\n";
    }

    void insert(int val)
    {
        Node *node = new Node(val);
        if (isEmpty())
        {
            this->val = val;
            next = nullptr;
            delete node;
            return;
        }
        Node *node2 = this;
        while (node2->next)
        {
            node2 = node2->next;
        }
        node2->next = node;
    }

    Node FindNode(int val)
    {
        Node *node = this;
        while (!node->isEmpty())
        {
            if (node->val == val)
            {
                return *node;
            }
            node = node->next;
        }
        throw -1;
    }

    Node FindPrev(Node node)
    {
        Node *head = this;
        if (*head == node)
        {
            throw -1;
        }
        Node *prev = head;
        while (!head->isEmpty())
        {
            if (*head == node)
            {
                return *prev;
            }
            prev = head;
            head = head->next;
        }
        throw -1;
    }

    Node FindNext(Node node)
    {
        Node *head = this;
        while (!head->isEmpty())
        {
            if (*head == node && head->next)
            {
                return *head->next;
            }
            head = head->next;
        }
        throw -1;
    }

    void DeleteList()
    {
        Node &node = *this;
        while (node.next)
        {
            Node &remove = node;
            node = *node.next;
            remove.DeleteNode();
        }
        node.DeleteNode();
    }

    void insertNext(Node node, int val)
    {
        Node head = *this;
        while (head != node)
        {
            head = *head.next;
            if (head.isEmpty())
            {
                throw -2;
            }
        }
        Node *a = head.next;
        Node *b = new Node(val);
        b->next = a;
        head.next = b;
    }

    void insertPrev(Node node, int val)
    {
        Node *head = this;
        if (node == *head)
        {
            Node *a = new Node(this->val);
            a->next = next;
            this->val = val;
            next = a;
            return;
        }
        Node *prev = head;
        while (!head->isEmpty())
        {
            ;
            // cout << head->next << " and " << pt.next << " ";
            if (node == *head)
            {
                Node *a = new Node;
                a->val = val;
                a->next = head;
                prev->next = a;
                return;
            }
            prev = head;
            head = head->next;
        }
        throw -2;
    }

    void DeleteNode(Node node)
    {
        Node *head = this;
        if (node == *head)
        {
            val = head->next->val;
            next = head->next->next;
            return;
        }
        Node *prev = head;
        while (!head->isEmpty())
        {
            if (*head == node)
            {
                prev->next = head->next;
                head->DeleteNode();
                delete head;
                return;
            }
            prev = head;
            head = head->next;
        }
    }
};

int main()
{
    Node n;
    n.insert(1);
    n.insert(2);
    n.insert(3);
    cout << "Вставили: 1, 2, 3\n";

    cout << "До и после 2\n";
    cout << n.FindPrev(n.FindNode(2)).getVal() << "\n";
    cout << n.FindNext(n.FindNode(2)).getVal() << "\n";

    cout << "Вставка перед вершиной node(1) значения 8\n";
    n.insertPrev(n.FindNode(1), 8);
     n.PrintList();
    // cout << n[3] << "\n";

    cout << "Оператор равно\n";
    Node p = n;
    p.PrintList();

    cout << "удалить \"вершину\" 3 и удалить список\n";
    n.DeleteNode(n.FindNode(3));
    n.PrintList();
    n.DeleteList();
    n.PrintList();
}
