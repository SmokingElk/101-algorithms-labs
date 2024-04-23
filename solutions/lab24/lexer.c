#include "lexer.h"

bool isDigit (char letter) {
    return '0' <= letter && letter <= '9';
}

bool isAlpha (char letter) {
    return 'a' <= letter && letter <= 'z';
}

bool isBracketOpen (char letter) {
    return letter == '(';
}

bool isBracketClose (char letter) {
    return letter == ')';
}

bool isOperator (char letter) {
    return strchr("+-*/^~", letter) != NULL;
}

LexerResult getLexemes (char *expr, Queue * outQueue) {
    int i = 0;

    while (expr[i] != '\0') {
        char letter = expr[i];

        if (isAlpha(letter)) {
            char *content = (char*)malloc(sizeof(char) * 2);
            content[0] = letter; content[1] = '\0';
            pushQueue(outQueue, newLexeme(VARIABLE, content));

        } else if (isOperator(letter)) {
            char *content = (char*)malloc(sizeof(char) * 2);
            content[0] = letter; content[1] = '\0';
            pushQueue(outQueue, newLexeme(OPERATOR, content));
            
        } else if (isBracketOpen(letter)) {
            char *content = (char*)malloc(sizeof(char) * 2);
            content[0] = letter; content[1] = '\0';
            pushQueue(outQueue, newLexeme(BRACKET_OPEN, content));

        } else if (isBracketClose(letter)) {
            char *content = (char*)malloc(sizeof(char) * 2);
            content[0] = letter; content[1] = '\0';
            pushQueue(outQueue, newLexeme(BRACKET_CLOSE, content));

        } else if (isDigit(letter)) {
            int j = i + 1;
            int numLen = 1;

            while (isDigit(expr[j])) { numLen++; j++; }

            char *content = (char*)malloc(sizeof(char) * (numLen + 1));
            for (j = 0; j < numLen; j++) content[j] = expr[i + j];
            content[numLen] = '\0';

            pushQueue(outQueue, newLexeme(NUMBER, content));

            i += numLen;
            continue;
        } else {
            return LR_ERROR_UNEXPECTED_LETTER;
        }

        i++;
    }

    return LR_SUCCESS;
}
