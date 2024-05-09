#include <iostream>
#include <cstring>

using namespace std;

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

struct TreeNode
{
    char value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

TreeNode *buildExpressionTree(const char *postfixExpression)
{
    Stack<TreeNode*> stack;
    int minus = 1;

    int len = strlen(postfixExpression);

    for (int i = 0; i < len; ++i)
    {
        char c = postfixExpression[i];
        if (isOperator(c))
        {
            if (c == '-' && (stack.isEmptyStack() || stack.topStack()->value != ' '))
            {
                minus *= -1;
                continue;
            }
            TreeNode *rightOperand = stack.topStack();
            stack.popStack();
            TreeNode *leftOperand;

            leftOperand = stack.topStack();
            stack.popStack();

            TreeNode *operatorNode = new TreeNode(c);

            operatorNode->left = leftOperand;

            operatorNode->right = rightOperand;

            stack.pushStack(operatorNode);
        }
        else
        {
            stack.pushStack(new TreeNode(c));
        }
    }

    if (minus == -1)
    {
        TreeNode *ret = new TreeNode('-');
        ret->right = stack.topStack();
        return ret;
    }

    return stack.topStack();
}

void printInorder(TreeNode *root)
{
    if (root)
    {
        printInorder(root->left);
        cout << root->value << " ";
        printInorder(root->right);
    }
}

char *infixToPostfix(const char *infixExpression)
{
    Stack<char> operators;
    int infixLength = strlen(infixExpression);
    char *postfixExpression = new char[infixLength + 1];
    int postfixIndex = 0;

    for (int i = 0; i < infixLength; ++i)
    {
        char c = infixExpression[i];
        if (isOperator(c))
        {
            while (!operators.isEmptyStack() && operators.topStack() != '(' && (c != '*' && c != '/') && (operators.topStack() == '+' || operators.topStack() == '-'))
            {
                postfixExpression[postfixIndex++] = operators.topStack();
                operators.popStack();
            }
            operators.pushStack(c);
        }
        else if (c == '(')
        {
            operators.pushStack(c);
        }
        else if (c == ')')
        {
            while (!operators.isEmptyStack() && operators.topStack() != '(')
            {
                postfixExpression[postfixIndex++] = operators.topStack();
                operators.popStack();
            }
            operators.popStack();
        }
        else if (c != ' ')
        {
            postfixExpression[postfixIndex++] = c;
        }
    }

    while (!operators.isEmptyStack())
    {
        postfixExpression[postfixIndex++] = operators.topStack();
        operators.popStack();
    }

    postfixExpression[postfixIndex] = '\0';

    return postfixExpression;
}

int main()
{
    char *infixExpression = "- ((a * (b)) * (4 * (5)))";
    char *postfixExpression = infixToPostfix(infixExpression);
    TreeNode *root = buildExpressionTree(postfixExpression);

    cout << "Инфиксная форма: " << infixExpression << "\n";
    cout << "Постфиксная форма: " << postfixExpression << "\n";
    cout << "Дерево: ";
    printInorder(root);
    cout << "\n";

    return 0;
}
