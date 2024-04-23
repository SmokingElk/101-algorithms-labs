#include "opClasses.h"

int opearationPriority (Lexeme *lexeme) {
    if (lexeme->type != OPERATOR) return -1;

    char operationSign = lexeme->content[0];

    switch (operationSign) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case '~':
            return 4;
        default:
            return -1;
    }
}

associativity operationAssociativity (Lexeme *lexeme) {
    if (lexeme->type != OPERATOR) return ASSOCIATIVE_NONE;

    char operationSign = lexeme->content[0];

    switch (operationSign) {
        case '+':
        case '-':
        case '*':
        case '/':
            return ASSOCIATIVE_LEFT;
        case '~':
        case '^':
            return ASSOCIATIVE_RIGHT;
        default:
            return ASSOCIATIVE_NONE;
    }
}

arity operationArity (Lexeme *lexeme) {
    if (lexeme->type != OPERATOR) return ARITY_NONE;

    char operationSign = lexeme->content[0];

    switch (operationSign) {
        case '~':
            return UNARY;
        default:
            return BINARY;
    }
}