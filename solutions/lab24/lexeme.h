#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

typedef enum {NUMBER, VARIABLE, BRACKET_OPEN, BRACKET_CLOSE, OPERATOR} lexemeType;

typedef struct {
    lexemeType type;
    char *content;
} Lexeme;

Lexeme* newLexeme (lexemeType type, char *content);
Lexeme* copyLexeme (Lexeme *lexeme);
void deleteLexeme (Lexeme *lexeme);
void printLexeme (Lexeme *lexeme);
void printLexemeContent (Lexeme *lexeme);