#include "stackPTN.h"

StackPTN* newStackPTN (int length) {
    StackPTN *res = (StackPTN*)malloc(sizeof(StackPTN));
    res->length = length;
    res->top = -1;
    if (length == 0) res->data = NULL;
    else res->data = (STACK_PTN_T*)malloc(sizeof(STACK_PTN_T) * length);

    return res;
}

void deleteStackPTN (StackPTN *stack, void (*deleteItem)(STACK_PTN_T item)) {    
    for (int i = 0; i < stack->top; i++) deleteItem(stack->data[i]);
    if (stack->data != NULL) free(stack->data);
    free(stack);
}

bool isEmptyStackPTN (StackPTN *stack) { return stack->top == -1; }
int sizeStackPTN (StackPTN *stack) { return stack->top + 1; }
STACK_PTN_T topStackPTN (StackPTN *stack) { return stack->data[stack->top]; }

void pushStackPTN (StackPTN *stack, STACK_PTN_T elem) {
    if (stack->top + 1 == stack->length || stack->length == 0) resizeStackPTN(stack);
    stack->top++;
    stack->data[stack->top] = elem;
}

void popStackPTN (StackPTN *stack, void (*deleteItem)(STACK_PTN_T item)) {
    deleteItem(stack->data[stack->top]);
    stack->top--;
}

void resizeStackPTN (StackPTN *stack) {
    STACK_PTN_T *newArray = (STACK_PTN_T *)malloc(sizeof(STACK_PTN_T) * (stack->length + STACK_PTN_RESIZE_STEP));
    for (int i = 0; i < stack->length; i++) newArray[i] = stack->data[i];

    if (stack->data != NULL) free(stack->data);
    stack->data = newArray;
    stack->length += STACK_PTN_RESIZE_STEP;
}