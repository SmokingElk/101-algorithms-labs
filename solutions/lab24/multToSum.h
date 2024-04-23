#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "stackPTN.h"
#include "lexeme.h"
#include "exprTree.h"

void splitToClasses (ExprTree tree, StackPTN *stackNums, StackPTN *stackVars, StackPTN *stackOther);
ExprTree reduceMult (ExprTree variableNode, int factor);
void deletePlug (ExprTree _);
void multToSum (ExprTree *treeP);
