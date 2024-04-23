#include "treeBuilder.h"

PostfixTranslateResult translateToPostfix (Queue *inputQueue, Queue *outputQueue) {
    // Dijkstra sorting station algorithm

    Stack *opStack = newStack(0);

    while (!isEmptyQueue(inputQueue)) {
        Lexeme *topLexeme = copyLexeme(topQueue(inputQueue));

        if (topLexeme->type == NUMBER || topLexeme->type == VARIABLE) pushQueue(outputQueue, topLexeme);

        if (topLexeme->type == OPERATOR) {
            int opPriority = opearationPriority(topLexeme);
            associativity opAssociativity = operationAssociativity(topLexeme);

            while (!isEmptyStack(opStack) && 
                (opAssociativity == ASSOCIATIVE_LEFT && opPriority <= opearationPriority(topStack(opStack)) ||
                opAssociativity == ASSOCIATIVE_RIGHT && opPriority < opearationPriority(topStack(opStack)))) {

                pushQueue(outputQueue, copyLexeme(topStack(opStack)));
                popStack(opStack, deleteLexeme);
            }

            pushStack(opStack, topLexeme);
        }

        if (topLexeme->type == BRACKET_OPEN) pushStack(opStack, topLexeme);
        
        if (topLexeme->type == BRACKET_CLOSE) {
            if (isEmptyStack(opStack)) {
                deleteStack(opStack, deleteLexeme);
                return PTR_ERROR_MISSING_OPEN_BRACKET;
            } 

            while (topStack(opStack)->type != BRACKET_OPEN) {
                pushQueue(outputQueue, copyLexeme(topStack(opStack)));
                popStack(opStack, deleteLexeme);

                if (isEmptyStack(opStack)) {
                    deleteStack(opStack, deleteLexeme);
                    return PTR_ERROR_MISSING_OPEN_BRACKET;
                } 
            }
            
            popStack(opStack, deleteLexeme);
        }

        popQueue(inputQueue, deleteLexeme);
    }
    
    while (!isEmptyStack(opStack)) {
        if (topStack(opStack)->type == BRACKET_OPEN) {
            deleteStack(opStack, deleteLexeme);
            return PTR_ERROR_MISSING_CLOSE_BRACKET;
        } 

        pushQueue(outputQueue, copyLexeme(topStack(opStack)));
        popStack(opStack, deleteLexeme);
    }

    deleteStack(opStack, deleteLexeme);

    return PTR_SUCCESS;
}

BuildTreeResult buildTree (Queue *inputQueue, ExprTree *tree, bool printPostfix) {
    Queue *lexemesPostfix = newQueue(0);
    PostfixTranslateResult ptrRes = translateToPostfix(inputQueue, lexemesPostfix);

    if (ptrRes == PTR_ERROR_MISSING_CLOSE_BRACKET) {
        deleteQueue(lexemesPostfix, deleteLexeme);
        return BT_ERROR_MISSING_CLOSE_BRACKET;
    }

    if (ptrRes == PTR_ERROR_MISSING_OPEN_BRACKET) {
        deleteQueue(lexemesPostfix, deleteLexeme);
        return BT_ERROR_MISSING_OPEN_BRACKET;
    }

    if (printPostfix) {
        printQueue(lexemesPostfix, deleteLexeme, copyLexeme, printLexemeContent);
    }

    StackPTN *stackPTN = newStackPTN(0);

    while (!isEmptyQueue(lexemesPostfix)) {
        Lexeme *topLexeme = copyLexeme(topQueue(lexemesPostfix));
        ExprTree treeNode = exprTreeFromLexeme(topLexeme);

        if (topLexeme->type == OPERATOR) {
            if (isEmptyStackPTN(stackPTN)) {
                deleteStackPTN(stackPTN, deleteExprTreeNode);
                deleteQueue(lexemesPostfix, deleteLexeme);
                return BT_ERROR_MISSING_OPERAND;
            }

            ExprTree childRight = copyExprTree(topStackPTN(stackPTN));
            popStackPTN(stackPTN, deleteExprTreeNode);
            
            ExprTree childLeft = NULL;
            
            if (operationArity(topLexeme) == BINARY) {
                if (isEmptyStackPTN(stackPTN)) {
                    deleteStackPTN(stackPTN, deleteExprTreeNode);
                    deleteQueue(lexemesPostfix, deleteLexeme);
                    return BT_ERROR_MISSING_OPERAND;
                }

                childLeft = copyExprTree(topStackPTN(stackPTN));
                popStackPTN(stackPTN, deleteExprTreeNode);
            }

            buildExprTree(treeNode, childLeft, childRight);
        }

        pushStackPTN(stackPTN, treeNode);
        popQueue(lexemesPostfix, deleteLexeme);
    }

    *tree = copyExprTree(topStackPTN(stackPTN));

    deleteStackPTN(stackPTN, deleteExprTreeNode);
    deleteQueue(lexemesPostfix, deleteLexeme);
    return BT_SUCCESS;
}