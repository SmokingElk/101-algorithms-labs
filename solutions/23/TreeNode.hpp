#ifndef TREENODE_H
#define TREENODE_H

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

#endif // TREENODE_H
