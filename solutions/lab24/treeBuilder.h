#pragma once
#include <stdbool.h>
#include "queue.h"
#include "stack.h"
#include "stackPTN.h"
#include "lexeme.h"
#include "opClasses.h"
#include "exprTree.h"

typedef enum {PTR_SUCCESS, PTR_ERROR_MISSING_CLOSE_BRACKET, PTR_ERROR_MISSING_OPEN_BRACKET} PostfixTranslateResult;

typedef enum {
    BT_SUCCESS, 
    BT_ERROR_MISSING_CLOSE_BRACKET, 
    BT_ERROR_MISSING_OPEN_BRACKET,
    BT_ERROR_MISSING_OPERAND
} BuildTreeResult;

PostfixTranslateResult translateToPostfix (Queue *inputQueue, Queue *outputQueue);
BuildTreeResult buildTree (Queue *inputQueue, ExprTree *tree, bool printPostfix);