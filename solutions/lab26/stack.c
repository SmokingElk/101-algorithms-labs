#include "stack.h"

Stack createStack (int maxSize) {
    Stack res = (Stack)malloc(sizeof(_Stack));
    res->top = -1;
    res->maxSize = maxSize;

    if (maxSize > 0) {
        res->elems = (STACK_T*)malloc(sizeof(STACK_T) * maxSize);
    } else res->elems = NULL;

    return res;
}

void deleteStack (Stack stack) {
    if (stack->elems != NULL) free(stack->elems);
    free(stack);
}

bool isEmptyStack (Stack stack) {
    return stack->top == -1;
}

int sizeStack (Stack stack) {
    return stack->top + 1;
}

STACK_T topStack (Stack stack) {
    return stack->elems[stack->top];
}

void pushStack (Stack stack, STACK_T elem) {
    stack->top++;
    if (stack->top >= stack->maxSize) _expandStack(stack, EXPAND_SIZE);
    stack->elems[stack->top] = elem;
}

STACK_T popStack (Stack stack) {
    return stack->elems[stack->top--];
}

void printStack (Stack stack) {
    for (int i = stack->top; i >= 0; i--) {
        printf("[[%5d]]HH>\n", stack->elems[i]);
    }
}

Stack concatStacks (Stack stack1, Stack stack2) {
    STACK_T top;
    int size1 = sizeStack(stack1), size2 = sizeStack(stack2);

    Stack res = createStack(size1 + size2);
    Stack inverter = createStack(size1 > size2 ? size1 : size2);
    
    while (!isEmptyStack(stack1)) {
        pushStack(inverter, popStack(stack1));
    }

    while (!isEmptyStack(inverter)) {
        top = popStack(inverter);
        pushStack(stack1, top);
        pushStack(res, top);
    }
    
    while (!isEmptyStack(stack2)) {
        pushStack(inverter, popStack(stack2));
    }

    while (!isEmptyStack(inverter)) {
        top = popStack(inverter);
        pushStack(stack2, top);
        pushStack(res, top);
    }

    deleteStack(inverter);
    return res;
}

void _expandStack (Stack stack, int expandSize) {
    STACK_T *newElems = (STACK_T*)malloc(sizeof(STACK_T) * (stack->maxSize + expandSize));
    
    if (stack->elems != NULL) {
        for (int i = 0; i <= stack->top; i++) newElems[i] = stack->elems[i];
        free(stack->elems);
    }

    stack->maxSize += expandSize;
    stack->elems = newElems;
}
