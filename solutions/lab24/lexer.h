#pragma once
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "lexeme.h"
#include "queue.h"

typedef enum {LR_SUCCESS, LR_ERROR_UNEXPECTED_LETTER} LexerResult;

bool isDigit (char letter);
bool isAlpha (char letter);
bool isBracketOpen (char letter);
bool isBracketClose (char letter);
bool isOperator (char letter);

LexerResult getLexemes (char *expr, Queue *outQueue);

