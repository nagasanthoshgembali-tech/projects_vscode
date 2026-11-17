#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 20

char stack[MAX];
int top = -1;

void push(char value) {
    stack[++top] = value;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '%' || c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

void intopost(char postfix[MAX], char infix[MAX]) {
    int i, j = 0;
    char ch;

    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            if (top != -1) {
                pop(); // Remove '('
            }
        } else {
            while (top != -1 && precedence(ch) <= precedence(stack[top]) && stack[top] != '(') {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main() {
    system("cls");
    char postfix[MAX], infix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    intopost(postfix, infix);
    printf("\nPostfix expression: %s\n", postfix);

    return 0;
}