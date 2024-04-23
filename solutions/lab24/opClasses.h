#pragma once
#include "lexeme.h"

typedef enum {ASSOCIATIVE_LEFT, ASSOCIATIVE_RIGHT, ASSOCIATIVE_NONE} associativity;
//typedef enum {}
typedef enum {UNARY, BINARY, ARITY_NONE} arity;

int opearationPriority (Lexeme *lexeme);
associativity operationAssociativity (Lexeme *lexeme);
arity operationArity (Lexeme *lexeme);