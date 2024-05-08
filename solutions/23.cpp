#include <iostream>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* nextSibling;
    TreeNode* firstChild;

    TreeNode(int val) : value(val), nextSibling(nullptr), firstChild(nullptr) {}
};

class Tree {
private:
    TreeNode* root;

     int countNodes(TreeNode* node) const {
        if (!node) return 0;
        int count = 1;
        count += countNodes(node->firstChild);
        count += countNodes(node->nextSibling);
        return count;
    }

    void freeNode(TreeNode* node) {
        if (!node) return;
        freeNode(node->firstChild);
        freeNode(node->nextSibling);
        delete node;
    }

    TreeNode* findNode(TreeNode* node, int value) {
        if (!node) return nullptr;
        if (node->value == value) return node;

        TreeNode* foundNode = findNode(node->firstChild, value);
        if (foundNode) return foundNode;

        return findNode(node->nextSibling, value);
    }

    TreeNode* findParent(TreeNode* node, TreeNode* child, TreeNode* parent = nullptr) {
        if (!node) return nullptr;
        if (node->firstChild == child) return node;

        TreeNode* foundParent = findParent(node->firstChild, child, node);
        if (foundParent) return foundParent;

        return findParent(node->nextSibling, child, parent);
    }

    void removeNodeLinks(TreeNode* parent, TreeNode* nodeToDelete) {
        if (!parent || !nodeToDelete) return;
        
        if (parent->firstChild == nodeToDelete) { 
            parent->firstChild = nodeToDelete->nextSibling;
        } else {
            TreeNode* temp = parent->firstChild;
            while (temp != nullptr && temp->nextSibling != nodeToDelete) {
                temp = temp->nextSibling;
            }
            if (temp != nullptr) {
                temp->nextSibling = nodeToDelete->nextSibling;
            }
        }
        nodeToDelete->nextSibling = nullptr;
        freeNode(nodeToDelete);
    }
    
    void printTree(TreeNode* node, int level = 0) const {
        if (node != nullptr) {
            for (int i = 0; i < level; i++) {
                cout << "  ";
            }
            cout << node->value << endl;

            printTree(node->firstChild, level + 1);

            printTree(node->nextSibling, level);
        }
    }

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        freeNode(root);
    }

    TreeNode* addNode(int value, int parentValue = -1) {
        if (parentValue == -1) {
            if (!root) {
                root = new TreeNode(value);
                return root;
            } else {
                cout << "Root already exists." << endl;
                return nullptr;
            }
        } else {
            TreeNode* parent = findNode(root, parentValue);
            if (parent) {
                TreeNode* newNode = new TreeNode(value);
                if (!parent->firstChild) {
                    parent->firstChild = newNode;
                } else {
                    TreeNode* temp = parent->firstChild;
                    while (temp->nextSibling) {
                        temp = temp->nextSibling;
                    }
                    temp->nextSibling = newNode;
                }
                return newNode;
            } else {
                cout << "Parent not found." << endl;
                return nullptr;
            }
        }
    }

    void deleteNode(int value) {
        if (!root) return;
        TreeNode* nodeToDelete = findNode(root, value);
        if (!nodeToDelete) return;
        
        if (nodeToDelete == root) {
            freeNode(root);
            root = nullptr;
            return;
        }
        
        TreeNode* parent = findParent(root, nodeToDelete);
        removeNodeLinks(parent, nodeToDelete);
    }

    void printTree() {
        printTree(root);
    }

    int countNodes() const {
        return countNodes(root);
    }
};

int main() {
    Tree myTree;

    myTree.addNode(1);
    myTree.addNode(2, 1);
    myTree.addNode(3, 1);
    myTree.addNode(4, 2);
    myTree.addNode(5, 2);
    myTree.addNode(6, 3);

    cout << "Initial tree:" << endl;
    myTree.printTree();
    cout << "Number of nodes in the tree: " << myTree.countNodes() << endl;
    
    cout << "After deleting node 2 and its subtree:" << endl;
    myTree.deleteNode(2);
    myTree.printTree();
    cout << "Number of nodes in the tree after deleting: " << myTree.countNodes() << endl;

    return 0;
}