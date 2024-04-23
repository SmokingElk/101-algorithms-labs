#include "lexeme.h"
#include "stdio.h"

Lexeme* newLexeme (lexemeType type, char *content) {
    Lexeme *res = (Lexeme*)malloc(sizeof(Lexeme));
    res->type = type;
    res->content = content;
    return res;
}

Lexeme* copyLexeme (Lexeme *lexeme) {
    char *contentCopy = (char*)malloc(sizeof(char) * strlen(lexeme->content) + 1);
    strcpy(contentCopy, lexeme->content);
    return newLexeme(lexeme->type, contentCopy);
}

void deleteLexeme (Lexeme *lexeme) {
    free(lexeme->content);
    free(lexeme);
}

void printLexeme (Lexeme *lexeme) {
    printf("Lexeme<");

    switch (lexeme->type) {
        case NUMBER: printf("NUMBER"); break;
        case VARIABLE: printf("VARIABLE"); break;
        case BRACKET_OPEN: printf("BRACKET_OPEN"); break;
        case BRACKET_CLOSE: printf("BRACKET_CLOSE"); break;
        case OPERATOR: printf("OPERATOR"); break;
    
        default:
            printf("UNDEFINED");
    }

    printf(">(\"%s\")\n", lexeme->content);
}

void printLexemeContent (Lexeme *lexeme) {
    printf("%s ", lexeme->content);
}