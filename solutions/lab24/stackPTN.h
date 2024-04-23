#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "exprTree.h"

#define STACK_PTN_RESIZE_STEP 10

typedef ExprTreeNode* STACK_PTN_T;

typedef struct {
    int length;
    int top;
    STACK_PTN_T *data;
} StackPTN;

StackPTN* newStackPTN (int length);
void deleteStackPTN (StackPTN *stack, void (*deleteItem)(STACK_PTN_T item));
bool isEmptyStackPTN (StackPTN *stack);
int sizeStackPTN (StackPTN *stack);
STACK_PTN_T topStackPTN (StackPTN *stack);
void pushStackPTN (StackPTN *stack, STACK_PTN_T elem);
void popStackPTN (StackPTN *stack, void (*deleteItem)(STACK_PTN_T item));
void resizeStackPTN (StackPTN *stack);