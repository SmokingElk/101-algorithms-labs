#include "stack.h"

Stack* newStack (int length) {
    Stack *res = (Stack*)malloc(sizeof(Stack));
    res->length = length;
    res->top = -1;
    if (length == 0) res->data = NULL;
    else res->data = (STACK_T*)malloc(sizeof(STACK_T) * length);

    return res;
}

void deleteStack (Stack *stack, void (*deleteItem)(STACK_T item)) {    
    for (int i = 0; i < stack->top; i++) deleteItem(stack->data[i]);
    if (stack->data != NULL) free(stack->data);
    free(stack);
}

bool isEmptyStack (Stack *stack) { return stack->top == -1; }
int sizeStack (Stack *stack) { return stack->top + 1; }
STACK_T topStack (Stack *stack) { return stack->data[stack->top]; }

void pushStack (Stack *stack, STACK_T elem) {
    if (stack->top + 1 == stack->length || stack->length == 0) resizeStack(stack);
    stack->top++;
    stack->data[stack->top] = elem;
}

void popStack (Stack *stack, void (*deleteItem)(STACK_T item)) {
    deleteItem(stack->data[stack->top]);
    stack->top--;
}

void resizeStack (Stack *stack) {
    STACK_T *newArray = (STACK_T *)malloc(sizeof(STACK_T) * (stack->length + STACK_RESIZE_STEP));
    for (int i = 0; i < stack->length; i++) newArray[i] = stack->data[i];

    if (stack->data != NULL) free(stack->data);
    stack->data = newArray;
    stack->length += STACK_RESIZE_STEP;
}