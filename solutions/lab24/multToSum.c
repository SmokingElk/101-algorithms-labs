#include "multToSum.h"

void splitToClasses (ExprTree tree, StackPTN *stackNums, StackPTN *stackVars, StackPTN *stackOther) {
    if (tree == NULL) return;

    if (tree->contentType == NUMBER) {
        pushStackPTN(stackNums, copyExprTree(tree));
        return;
    }

    if (tree->contentType == VARIABLE) {
        pushStackPTN(stackVars, copyExprTree(tree));
        return;
    }

    if (tree->content[0] != '*') {
        pushStackPTN(stackOther, copyExprTree(tree));
        return;
    }

    splitToClasses(tree->childLeft, stackNums, stackVars, stackOther);
    splitToClasses(tree->childRight, stackNums, stackVars, stackOther);
}

ExprTree reduceMult (ExprTree variableNode, int factor) {
    if (factor == 0) return newExprTree(NUMBER, "0");
    if (factor == 1) return copyExprTree(variableNode);
    
    ExprTree res = newExprTree(OPERATOR, "+");

    res->childLeft = copyExprTree(variableNode);
    res->childRight = copyExprTree(variableNode);

    for (int i = 2; i < factor; i++) {
        res->childRight = buildExprTree(newExprTree(OPERATOR, "+"), copyExprTree(variableNode), res->childRight);
    }
    
    return res;
}

void deletePlug (ExprTree _) {}

void multToSum (ExprTree *treeP) {
    ExprTree tree = *treeP;

    if (tree == NULL) return;

    if (tree->contentType != OPERATOR || tree->content[0] != '*') {
        multToSum(&(*treeP)->childLeft);
        multToSum(&(*treeP)->childRight);
        return;
    }

    StackPTN *stackNums = newStackPTN(0);
    StackPTN *stackVars = newStackPTN(0);
    StackPTN *stackOther = newStackPTN(0);
    
    splitToClasses(tree, stackNums, stackVars, stackOther);

    if (isEmptyStackPTN(stackNums) || isEmptyStackPTN(stackVars)) {
        deleteStackPTN(stackNums, deleteExprTreeNode);
        deleteStackPTN(stackVars, deleteExprTreeNode);
        deleteStackPTN(stackOther, deleteExprTreeNode);

        multToSum(&(*treeP)->childLeft);
        multToSum(&(*treeP)->childRight);
        return;
    }

    StackPTN *stackCommon = newStackPTN(0);

    while (!isEmptyStackPTN(stackVars) && !isEmptyStackPTN(stackNums)) {
        ExprTree variableNode = topStackPTN(stackVars);
        int factor = extractNumber(topStackPTN(stackNums));

        ExprTree reduceRes = reduceMult(variableNode, factor);

        pushStackPTN(stackCommon, reduceRes);
        popStackPTN(stackVars, deleteExprTreeNode);
        popStackPTN(stackNums, deleteExprTreeNode);
    }
    
    while (!isEmptyStackPTN(stackVars)) {
        pushStackPTN(stackCommon, copyExprTree(topStackPTN(stackVars)));
        popStackPTN(stackVars, deleteExprTreeNode);
    }

    while (!isEmptyStackPTN(stackNums)) {
        pushStackPTN(stackCommon, copyExprTree(topStackPTN(stackNums)));
        popStackPTN(stackNums, deleteExprTreeNode);
    }
    
    while (!isEmptyStackPTN(stackOther)) {
        ExprTree topOther = topStackPTN(stackOther);
        multToSum(&topOther->childLeft);
        multToSum(&topOther->childRight);
        pushStackPTN(stackCommon, deepCopyExprTree(topOther));
        popStackPTN(stackOther, deletePlug);
        deleteExprTreeNode(topOther);
    }

    ExprTree newTree;
    if (sizeStackPTN(stackCommon) == 1) {
        newTree = copyExprTree(topStackPTN(stackCommon));
        popStackPTN(stackCommon, deleteExprTreeNode);
    } else {
        newTree = newExprTree(OPERATOR, "*");

        newTree->childLeft = copyExprTree(topStackPTN(stackCommon));
        popStackPTN(stackCommon, deleteExprTreeNode);

        newTree->childRight = copyExprTree(topStackPTN(stackCommon));
        popStackPTN(stackCommon, deleteExprTreeNode);

        while (!isEmptyStackPTN(stackCommon)) {
            newTree->childRight = buildExprTree(
                newExprTree(OPERATOR, "*"), 
                copyExprTree(topStackPTN(stackCommon)), 
                newTree->childRight
            );

            popStackPTN(stackCommon, deleteExprTreeNode);
        }  
    } 

    deleteExprTree(tree);

    *treeP = newTree;

    deleteStackPTN(stackNums, deleteExprTreeNode);
    deleteStackPTN(stackVars, deleteExprTreeNode);
    deleteStackPTN(stackOther, deleteExprTreeNode);
    deleteStackPTN(stackCommon, deleteExprTreeNode);
}