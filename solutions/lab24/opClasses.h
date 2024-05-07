#pragma once
#include "lexeme.h"

typedef enum {UNARY, BINARY, ARITY_NONE} arity;
typedef enum {COMMUTATIVE, NOT_COMMUTATIVE, COMMUTATIVE_NONE} commutativity;
typedef enum {ASSOCIATIVE_LEFT, ASSOCIATIVE_RIGHT, ASSOCIATIVE_NONE} associativity;

int opearationPriority (Lexeme *lexeme);
associativity operationAssociativity (Lexeme *lexeme);
commutativity operationCommutativity (Lexeme *lexeme);
arity operationArity (Lexeme *lexeme);