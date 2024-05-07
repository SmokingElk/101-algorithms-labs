#include "exprTree.h"

ExprTree newExprTree (lexemeType contentType, char *content) {
    ExprTree res = (ExprTree)malloc(sizeof(ExprTreeNode));
    res->content = NULL;

    setContentExprTree(res, contentType, content);

    res->childLeft = NULL;
    res->childRight = NULL;

    return res;
}

void deleteExprTreeNode (ExprTree tree) {
    free(tree->content);
    free(tree);
}

ExprTree exprTreeFromLexeme (Lexeme *lexeme) {
    return newExprTree(lexeme->type, lexeme->content);
}

ExprTree copyExprTree (ExprTree tree) {
    ExprTree res = newExprTree(tree->contentType, tree->content);

    res->childLeft = tree->childLeft;
    res->childRight = tree->childRight;

    return res;
}

ExprTree deepCopyExprTree (ExprTree tree) {
    ExprTree res = newExprTree(tree->contentType, tree->content);

    if (tree->childLeft != NULL) res->childLeft = deepCopyExprTree(tree->childLeft);
    if (tree->childRight != NULL) res->childRight = deepCopyExprTree(tree->childRight);

    return res;
}

void setContentExprTree (ExprTree tree, lexemeType contentType, char *content) {
    if (tree->content != NULL) free(tree->content);

    tree->content = (char*)malloc(sizeof(char) * (strlen(content) + 1));
    strcpy(tree->content, content);

    tree->contentType = contentType;
}

ExprTree buildExprTree (ExprTree root, ExprTree childLeft, ExprTree childRight) {
    if (root->childLeft != NULL) deleteExprTree(childLeft);
    if (root->childRight != NULL) deleteExprTree(childRight);
    root->childLeft = childLeft;
    root->childRight = childRight;
    return root;
}

ExprTree left (ExprTree tree) {
    return tree->childLeft;
}

ExprTree right (ExprTree tree) {
    return tree->childRight;
}

bool isTerm (ExprTree tree) {
    return tree->childLeft == NULL && tree->childRight == NULL;
}

int extractNumber (ExprTree tree) {
    if (tree->contentType != NUMBER) return 0;
    return atoi(tree->content);
}

int nodeOperationPriority (ExprTree node) {
    char *contentCopy = (char*)malloc(sizeof(char) * strlen(node->content + 1));
    strcpy(contentCopy, node->content);

    Lexeme *lexTmp = newLexeme(node->contentType, contentCopy);
    int priority = opearationPriority(lexTmp);

    deleteLexeme(lexTmp);
    return priority;
}

commutativity nodeOperationCommutativity (ExprTree node) {
    char *contentCopy = (char*)malloc(sizeof(char) * strlen(node->content + 1));
    strcpy(contentCopy, node->content);

    Lexeme *lexTmp = newLexeme(node->contentType, contentCopy);
    commutativity res = operationCommutativity(lexTmp);

    deleteLexeme(lexTmp);
    return res;
}

associativity nodeOperationAssociativity (ExprTree node) {
    char *contentCopy = (char*)malloc(sizeof(char) * strlen(node->content + 1));
    strcpy(contentCopy, node->content);

    Lexeme *lexTmp = newLexeme(node->contentType, contentCopy);
    associativity res = operationAssociativity(lexTmp);

    deleteLexeme(lexTmp);
    return res;
}

void deleteExprTree (ExprTree tree) {
    if (tree->childLeft != NULL) deleteExprTree(tree->childLeft);
    if (tree->childRight != NULL) deleteExprTree(tree->childRight);
    deleteExprTreeNode(tree);
}

void printExprTree (ExprTree tree, int level) {
    if (tree == NULL) return;

    for (int i = 0; i < level; i++) printf(" ");
    printf("%s\n", tree->content);
    printExprTree(tree->childLeft, level + 1);
    printExprTree(tree->childRight, level + 1);
}

void printTreeAsExpr (ExprTree tree) {
    int rootPriority = nodeOperationPriority(tree);

    if (tree->childLeft != NULL) {
        bool wrapLeft = tree->childLeft->contentType == OPERATOR && nodeOperationPriority(tree->childLeft) < rootPriority;
        if (wrapLeft) printf("(");
        printTreeAsExpr(tree->childLeft);
        if (wrapLeft) printf(")");
    }

    printf("%s", tree->content);

    if (tree->childRight != NULL) {
        int rightPriority = nodeOperationPriority(tree->childRight);

        bool isRightOperator = tree->childRight->contentType == OPERATOR;
        bool lowPriority = isRightOperator && rightPriority < rootPriority;
        bool notCommutative = nodeOperationCommutativity(tree) == NOT_COMMUTATIVE;
        bool isRootRightAssoc = nodeOperationAssociativity(tree) == ASSOCIATIVE_RIGHT;
        bool equalPriorityNotCommutative = notCommutative && isRightOperator && rightPriority == rootPriority && !isRootRightAssoc;
        bool wrapRight = lowPriority || equalPriorityNotCommutative;

        if (wrapRight) printf("(");
        printTreeAsExpr(tree->childRight);
        if (wrapRight) printf(")");
    }
}