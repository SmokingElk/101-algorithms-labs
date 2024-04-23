#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lexeme.h"
#include "stack.h"
#include "queue.h"
#include "lexer.h"
#include "treeBuilder.h"
#include "multToSum.h"

#define DETAILS_KEY "-i"

int main (int argc, char *argv[]) {
    bool printDetails = argc > 1 && strcmp(argv[1], DETAILS_KEY) == 0;

    printf("Input your expression: ");

    char expr[50];
    scanf("%s", expr);

    Queue *lexemesInfix = newQueue(0);
    LexerResult lexerRes = getLexemes(expr, lexemesInfix);

    if (lexerRes == LR_ERROR_UNEXPECTED_LETTER) {
        printf("Error: unexpected letter in expression.\n");
        return 1;
    }

    if (printDetails) {
        printf("\nSource expression divided into lexemes:\n");
        printQueue(lexemesInfix, deleteLexeme, copyLexeme, printLexeme);
        printf("\nExpression in postfix form: ");
    }

    ExprTree tree;
    BuildTreeResult buildTreeRes = buildTree(lexemesInfix, &tree, printDetails);

    if (buildTreeRes == BT_ERROR_MISSING_OPEN_BRACKET) {
        printf("Error: missing open bracket.\n");
        return 2;
    }

    if (buildTreeRes == BT_ERROR_MISSING_CLOSE_BRACKET) {
        printf("Error: missing close bracket.\n");
        return 2;
    }

    if (buildTreeRes == BT_ERROR_MISSING_OPERAND) {
        printf("Error: missing operand.\n");
        return 2;
    }

    if (printDetails) {
        printf("\n\nSource expression's tree:\n");
        printExprTree(tree, 0);
        printf("\n");
    }

    multToSum(&tree);

    if (printDetails) {
        printf("Processed expression's tree:\n");
        printExprTree(tree, 0);
        printf("\n");
    }

    printf("Processed expression: ");
    printTreeAsExpr(tree);
    printf("\n");
    
    deleteExprTree(tree);
    deleteQueue(lexemesInfix, deleteLexeme);
    return 0;
}
