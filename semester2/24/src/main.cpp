#include "../include/ExpressionTree.hpp"
#include <iostream>
#include <string>

int main() {
    string infix = "4*a/2";
    ExpressionTree tree;
    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    tree.build(postfix);
    cout << "Original Expression Tree: ";
    tree.display();

    tree.simplifyTree();
    cout << "Simplified Expression Tree: ";
    tree.display();

    return 0;
}
