#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "lexeme.h"

#define STACK_RESIZE_STEP 10

typedef Lexeme* STACK_T;

typedef struct {
    int length;
    int top;
    STACK_T *data;
} Stack;

Stack* newStack (int length);
void deleteStack (Stack *stack, void (*deleteItem)(STACK_T item));
bool isEmptyStack (Stack *stack);
int sizeStack (Stack *stack);
STACK_T topStack (Stack *stack);
void pushStack (Stack *stack, STACK_T elem);
void popStack (Stack *stack, void (*deleteItem)(STACK_T item));
void resizeStack (Stack *stack);