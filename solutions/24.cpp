#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// Структура для представления узла дерева выражений
struct Node {
    string value; // Значение узла (оператор или операнд)
    Node* left;        // Левый дочерний узел
    Node* right;       // Правый дочерний узел

    // Конструктор для инициализации узла значением
    Node(const string& val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для построения дерева выражений для выражения ad
Node* buildExpressionTreeAD(int a, int d) {
    Node* root = new Node("*");
    root->left = new Node(to_string(a));
    root->right = new Node(to_string(d));
    return root;
}

// Функция для построения дерева выражений для выражения bc
Node* buildExpressionTreeBC(int b, int c) {
    Node* root = new Node("*");
    root->left = new Node(to_string(b));
    root->right = new Node(to_string(c));
    return root;
}

// Функция для построения дерева выражений для выражения bd
Node* buildExpressionTreeBD(int b, int d) {
    Node* root = new Node("*");
    root->left = new Node(to_string(b));
    root->right = new Node(to_string(d));
    return root;
}

// Функция для построения дерева выражений для выражения (ad+bc)/(bd)
Node* buildExpressionTree(int a, int b, int c, int d) {
    // Построение дерева для выражения ad
    Node* ad = buildExpressionTreeAD(a, d);

    // Построение дерева для выражения bc
    Node* bc = buildExpressionTreeBC(b, c);

    // Построение дерева для выражения bd
    Node* bd = buildExpressionTreeBD(b, d);

    // Построение дерева для выражения ad+bc
    Node* adPlusBc = new Node("+");
    adPlusBc->left = ad;
    adPlusBc->right = bc;

    // Построение корневого узла дерева для выражения (ad+bc)/(bd)
    Node* root = new Node("/");
    root->left = adPlusBc;
    root->right = bd;

    return root;
}

// Функция для вывода дерева выражений в понятном виде
void printExpressionTree(const Node* node, int level = 0) {
    if (node == nullptr) return;

    printExpressionTree(node->right, level + 1);
    for (int i = 0; i < level; ++i) {
        cout << "   ";
    }
    cout << node->value << endl;
    printExpressionTree(node->left, level + 1);
}

// Функция для удаления дерева выражений из памяти
void deleteExpressionTree(Node* node) {
    if (node == nullptr) return;

    deleteExpressionTree(node->left);
    deleteExpressionTree(node->right);
    delete node;
}

// Функция для парсинга выражения и извлечения значений a, b, c, d
bool parseExpression(const string& expression, int& a, int& b, int& c, int& d) {
    istringstream iss(expression);
    char op1, op2, div1, div2;
    iss >> a >> div1 >> b >> op1 >> c >> div2 >> d;
    return div1 == '/' && div2 == '/' && op1 == '+';
}

// Функция для разделения выражения на части a/b и c/d
bool splitExpression(const string& expression, string& part1, string& part2) {
    size_t plusPos = expression.find('+');
    if (plusPos == string::npos) return false;
    part1 = expression.substr(0, plusPos);
    part2 = expression.substr(plusPos + 1);
    return true;
}

// Функция для извлечения значений a, b, c, d из частей выражения
bool extractValues(const string& part1, const string& part2, int& a, int& b, int& c, int& d) {
    istringstream iss1(part1), iss2(part2);
    char div1, div2;
    iss1 >> a >> div1 >> b;
    iss2 >> c >> div2 >> d;
    return div1 == '/' && div2 == '/';
}

int main() {
    string expression;
    cout << "Enter expr in format a/b+c/d: ";
    getline(cin, expression);

    string part1, part2;
    if (!splitExpression(expression, part1, part2)) {
        cerr << "Error: incorrect input format." << endl;
        return 1;
    }

    int a, b, c, d;
    if (!extractValues(part1, part2, a, b, c, d)) {
        cerr << "Error: incorrect input format." << endl;
        return 1;
    }

    if (b == 0 || d == 0) {
        cerr << "Error: division by zero is not allowed." << endl;
        return 1;
    }

    Node* root = buildExpressionTree(a, b, c, d);

    cout << "Expr tree for (ad+bc)/(bd):" << endl;
    printExpressionTree(root);

    // Удаляем дерево выражений
    deleteExpressionTree(root);

    return 0;
}