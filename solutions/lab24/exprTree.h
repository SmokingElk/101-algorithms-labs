#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lexeme.h"
#include "opClasses.h"

typedef struct __ExprTreeNode {
    char *content;
    lexemeType contentType;

    struct __ExprTreeNode *childLeft;
    struct __ExprTreeNode *childRight;
} ExprTreeNode;

typedef ExprTreeNode* ExprTree;

ExprTree newExprTree(lexemeType contentType, char *content);
void deleteExprTreeNode (ExprTree tree);
ExprTree exprTreeFromLexeme (Lexeme *lexeme);
ExprTree copyExprTree (ExprTree tree);
ExprTree deepCopyExprTree (ExprTree tree);
void setContentExprTree (ExprTree tree, lexemeType contentType, char *content);
ExprTree buildExprTree (ExprTree root, ExprTree childLeft, ExprTree childRight);
ExprTree left (ExprTree tree);
ExprTree right (ExprTree tree);
bool isTerm (ExprTree tree);
int extractNumber (ExprTree tree);
int nodeOperationPriority (ExprTree node);
commutativity nodeOperationCommutativity (ExprTree node);
associativity nodeOperationAssociativity (ExprTree node);
void deleteExprTree (ExprTree tree);

void printExprTree (ExprTree tree, int level);
void printTreeAsExpr (ExprTree tree);