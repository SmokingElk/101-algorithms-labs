#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ExpressionNode {
    char exp;
    int value;
    struct ExpressionNode* lt;
    struct ExpressionNode* rt;
} ExpressionNode;

ExpressionNode* newExpressionNode(char exp) {
    ExpressionNode* node = (ExpressionNode*)malloc(sizeof(ExpressionNode));
    node->exp = exp;
    node->value = 0;
    node->lt = NULL;
    node->rt = NULL;
    return node;
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

char* PolishEntry(const char* expression, int len) {
    char* stack = (char*)malloc(len * sizeof(char));
    int top = -1;
    char* rpn = (char*)malloc((len + 1) * sizeof(char));
    int index = 0;

    for (int i = 0; i < len; ++i) {
        char c = expression[i];
        if (isdigit(c)) {
            rpn[index++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') {
                rpn[index++] = stack[top--];
            }
            if (top >= 0 && stack[top] == '(') {
                --top;
            }
        } else {
            while (top >= 0 && precedence(c) <= precedence(stack[top])) {
                rpn[index++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top >= 0) {
        rpn[index++] = stack[top--];
    }

    rpn[index] = '\0';
    free(stack);
    return rpn;
}

void Solution(const char* expression, int len) {
    for (int i = len - 1; i >= 0; --i) {
        if (expression[i] == '\0')
            continue;
        if (expression[i] == '*') {
            if (expression[i + 1] == '0') {
                continue;
            }
        } else if (expression[i] != '0') {
            printf("%c", expression[i]);
        }
    }
    printf("\n");
}

int main() {
    const char* expression = "(3+3)*(2+1)";
    int len = strlen(expression);
    char* res = PolishEntry(expression, len);
    printf("Current Expression\n");
    printf("%s\n", res);
    Solution(res, len);
    free(res);
    return 0;
}