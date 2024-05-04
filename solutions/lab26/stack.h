#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define EXPAND_SIZE 10

typedef int STACK_T;

typedef struct {
    STACK_T *elems;
    int maxSize;
    int top;
} _Stack;

typedef _Stack* Stack;

// public
Stack createStack (int maxSize);
void deleteStack (Stack stack);
bool isEmptyStack (Stack stack);
int sizeStack (Stack stack);
STACK_T topStack (Stack stack);
void pushStack (Stack stack, STACK_T elem);
STACK_T popStack (Stack stack);
void printStack (Stack stack);
Stack concatStacks (Stack stack1, Stack stack2);

// protected
void _expandStack (Stack stack, int expandSize);