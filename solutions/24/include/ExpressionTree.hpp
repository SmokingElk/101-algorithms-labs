#ifndef EXPRESSIONTREE_HPP
#define EXPRESSIONTREE_HPP

#include "ExpressionNode.hpp"
#include <stack>
#include <iostream>

class ExpressionTree {
private:
    ExpressionNode* root;

    void simplify(ExpressionNode* node) {
        if (!node) return;
        simplify(node->left);
        simplify(node->right);

        if (node->value == "/" && node->right && node->right->value == "2") {
            if (node->left && node->left->value == "*" &&
                ((node->left->left && node->left->left->value == "4") || (node->left->right && node->left->right->value == "4"))) {
                node->value = "*";
                node->right->value = "2";

                if (node->left->left && node->left->left->value == "4") {
                    node->left->left->value = "2";
                } else {
                    node->left->right->value = "2";
                }

                ExpressionNode* temp = node->left->right;
                node->left = temp;
            }
        }
    }

public:
    ExpressionTree() : root(nullptr) {}
    ~ExpressionTree() {
        delete root;
    }

    friend int precedence(char op);
    friend string infixToPostfix(const string& infix);

    void build(const std::string& postfix) {
        stack<ExpressionNode*> stack;
        string operators = "+-*/";

        for (char ch : postfix) {
            string value(1, ch);
            if (operators.find(ch) != string::npos) {
                ExpressionNode* right = stack.top(); stack.pop();
                ExpressionNode* left = stack.top(); stack.pop();
                ExpressionNode* node = new ExpressionNode(value);
                node->left = left;
                node->right = right;
                stack.push(node);
            } else {
                stack.push(new ExpressionNode(value));
            }
        }

        root = stack.top();
    }

    void simplifyTree() {
        simplify(root);
    }

    void printInfix(ExpressionNode* node) {
        if (!node) return;
        if (node->left) cout << "(";
        printInfix(node->left);
        cout << node->value;
        printInfix(node->right);
        if (node->right) cout << ")";
    }

    void display() {
        printInfix(root);
        cout << endl;
    }
};

int precedence(char op) {
    if(op == '+' || op == '-') {
        return 1;
    }
    if(op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

string infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix = "";

    for (char c : infix) {
        if (isdigit(c) || isalpha(c)) {
            postfix += c;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

#endif //EXPRESSIONTREE_HPP
