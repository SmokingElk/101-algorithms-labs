#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype> // Для функции isdigit

using namespace std;

struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

TreeNode* buildExpressionTree(const string& postfixExpression) {
    stack<TreeNode*> stack;

    for (char c : postfixExpression) {
        if (isOperator(c)) {
            TreeNode* rightOperand = stack.top();
            stack.pop();
            TreeNode* leftOperand;

            leftOperand = stack.top();
            stack.pop();

            TreeNode* operatorNode = new TreeNode(c);

            operatorNode->left = leftOperand;

            operatorNode->right = rightOperand;

            stack.push(operatorNode);
        }
        else {
            stack.push(new TreeNode(c));
        }
    }

    return stack.top();
}

void printInorder(TreeNode* root) {
    if (root) {
        printInorder(root->left);
        cout << root->value << " ";
        printInorder(root->right);
    }
}

string infixToPostfix(const string& infixExpression) {
    stack<char> operators;
    string postfixExpression;

    for (char c : infixExpression) {
        if (isOperator(c)) {
            // Если символ - оператор, извлекаем все операторы с более высоким или равным приоритетом из стека
            // и добавляем их к постфиксной строке, затем добавляем текущий оператор в стек
            while (!operators.empty() && operators.top() != '(' && (c != '*' && c != '/') && (operators.top() == '+' || operators.top() == '-')) {
                postfixExpression += operators.top();
                operators.pop();
            }
            operators.push(c);
        } else if (c == '(') {
            operators.push(c); // Если символ - открывающая скобка, добавляем её в стек
        } else if (c == ')') {
            // Если символ - закрывающая скобка, извлекаем все операторы из стека до открывающей скобки
            // и добавляем их к постфиксной строке, затем удаляем открывающую скобку из стека
            while (!operators.empty() && operators.top() != '(') {
                postfixExpression += operators.top();
                operators.pop();
            }
            operators.pop(); // Удаляем открывающую скобку из стека
        } else if (c != ' '){
            postfixExpression += c; // Если символ - операнд, добавляем его к постфиксной строке
        }
    }

    // Извлекаем оставшиеся операторы из стека и добавляем их к постфиксной строке
    while (!operators.empty()) {
        postfixExpression += operators.top();
        operators.pop();
    }

    return postfixExpression;
}

int countAndRemoveMinusSigns(string& str) {
    int count = 0;
    size_t pos = 0;
    while ((pos = str.find('-')) != string::npos) {
        str.erase(pos, 1);
        count++;
    }
    return count;
}

int main() {
    string infixExpression = "a * (-b) * 4 * (-5)";
    int minuses = (countAndRemoveMinusSigns(infixExpression)) % 2;
    string postfixExpression = infixToPostfix(infixExpression);
    TreeNode* root = buildExpressionTree(postfixExpression);

    cout << "Дерево разбора для выражения " << postfixExpression << ":\n";
    if (minuses % 2 == 1)
        cout << "- ";
    printInorder(root);
    cout << "\n\n";

    return 0;
}
