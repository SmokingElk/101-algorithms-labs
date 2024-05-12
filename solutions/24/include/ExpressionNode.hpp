#ifndef EXPRESSIONNODE_HPP
#define EXPRESSIONNODE_HPP

#include <string>

using namespace std;

class ExpressionNode {
public:
    string value;
    ExpressionNode* left;
    ExpressionNode* right;

    ExpressionNode(const string &val) : value(val), left(nullptr), right(nullptr) {}
};

#endif //EXPRESSIONNODE_HPP
