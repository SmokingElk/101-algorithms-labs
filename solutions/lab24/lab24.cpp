#include <iostream>
#include <stack>
#include <string.h>


struct ExpressionNode{
    char exp;
    int value;
    ExpressionNode* lt;
    ExpressionNode* rt;

    ExpressionNode(char exp): exp(exp), value(0), lt(nullptr), rt(nullptr){}
    ExpressionNode(int value): exp('\0'), value(value), lt(nullptr), rt(nullptr){}

};
    


int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}


char* PolishEntry(const char* expression, int len){
    std::stack<char> operators;
    char* rpn = new char[len];
    int index = 0;

    for (int i = 0; i < len; ++i) {
        char c = expression[i];
        // Если символ цифра, добавляем его к результату
        if (isdigit(c)) {
            rpn[index++] = c;
        }
        // Если символ открывающая скобка, помещаем ее в стек
        else if (c == '(') {
            operators.push(c);
        }
        // Если символ закрывающая скобка, выталкиваем все операторы до открывающей скобки
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                rpn[index++] = operators.top();
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
        }
        // Если символ оператор, выталкиваем все операторы с большим или равным приоритетом
        else {
            while (!operators.empty() && precedence(c) <= precedence(operators.top())) {
                rpn[index++] = operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    // Выталкиваем все оставшиеся операторы из стека
    while (!operators.empty()) {
        rpn[index++] = operators.top();
        operators.pop();
    }

    rpn[index] = '\0'; // Завершаем строку символом конца строки
    return rpn;
}


void Solution(const char* expression, int len){
    for (int i = len - 1; i >= 0; --i){
        if (expression[i] == '\0');
            continue;
        if (expression[i] == '*'){
            if (expression[i + 1] == '0'){
                continue;
            }
        }
        else if (expression[i] != '0'){
            std::cout << expression[i];
        }
        
    }
    std::cout << '\n';
}


int main(){
    const char* expression = "(3+3)*(2+1)";
    int len = strlen(expression);
    char* res = PolishEntry(expression, len);
    std::cout << "Current Expression" << "\n";
    std::cout << res << "\n";
    Solution(res, len);

}