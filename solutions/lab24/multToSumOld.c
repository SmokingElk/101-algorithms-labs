#include "multToSum.h"

bool isNodeProcessable (ExprTree tree) {
    if (tree->contentType != OPERATOR) return false;
    if (tree->content[0] != '*') return false;
    if (tree->childLeft == NULL || tree->childRight == NULL) return false;
    
    bool hasFactor = tree->childLeft->contentType == NUMBER || tree->childRight->contentType == NUMBER;
    bool hasVar = tree->childLeft->contentType == VARIABLE || tree->childRight->contentType == VARIABLE;
    return hasFactor && hasVar;
}

void multToSum (ExprTree tree) {
    if (!isNodeProcessable(tree)) {
        if (tree->childLeft != NULL) multToSum(tree->childLeft);
        if (tree->childRight != NULL) multToSum(tree->childRight);
        return;
    }

    // extractNumber возвращает 0, если тип узла не является числом
    // т.к. один из дочерних узлов имеет тип число, а второй - нет, сумма будет равна значению множителя
    int termsCount = extractNumber(tree->childLeft) + extractNumber(tree->childRight);

    ExprTree variableNode = copyExprTree(tree->childLeft->contentType == VARIABLE ? tree->childLeft : tree->childRight);

    deleteExprTreeNode(tree->childLeft);
    deleteExprTreeNode(tree->childRight);

    setContentExprTree(tree, OPERATOR, "+");

    tree->childLeft = termsCount > 1 ? copyExprTree(variableNode) : newExprTree(NUMBER, "0");
    tree->childRight = termsCount > 0 ? copyExprTree(variableNode) : newExprTree(NUMBER, "0");

    for (int i = 2; i < termsCount; i++) {
        tree->childRight = buildExprTree(newExprTree(OPERATOR, "+"), copyExprTree(variableNode), tree->childRight);
    }

    deleteExprTreeNode(variableNode);
}