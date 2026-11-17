#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stack.h>

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

// Function to check if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Function to convert infix to postfix expression
void infixToPostfix(char* infix, char* postfix) {
    stack_t s;
    int top;

    // Initialize stack
    s.top = -1;
    // Allocate space for the stack (assuming a reasonable max size for simplicity)
    // In a real scenario, dynamic allocation or a more robust structure would be better.
    char stack[100]; 

    // Clear stack
    for (int i = 0; i < 100; i++) {
        stack[i] = '\0';
    }

    // Process infix expression
    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        if (isalnum(token)) {
            // Operand: append to postfix string
            strcat(postfix, &token);
            strcat(postfix, " ");
        } else if (isOperator(token)) {
            // Operator: pop while stack top has greater or equal precedence
            while (s.top != -1 && precedence(stack[s.top]) >= precedence(token)) {
                char popped = stack[s.top];
                s.top--;
                // Append the operator to postfix string
                strcat(postfix, &popped);
                strcat(postfix, " ");
            }
            // Push current operator onto stack
            if (s.top < 99) { // Check for stack overflow
                stack[++s.top] = token;
            } else {
                fprintf(stderr, "Error: Stack overflow during infix to postfix conversion.\n");
                return;
            }
        }
    }

    // Pop remaining operators from stack
    while (s.top != -1) {
        char popped = stack[s.top];
        s.top--;
        strcat(postfix, &popped);
        strcat(postfix, " ");
    }
    strcat(postfix, "\0"); // Null-terminate the postfix string
}

// Function to convert postfix to prefix expression (Reverse Postfix)
void infixToPrefix(char* postfix, char* prefix) {
    int len = strlen(postfix);
    for (int i = 0; i < len; i++) {
        prefix[i] = '\0';
    }

    // Reverse the postfix string to get the prefix expression
    for (int i = len - 1; i >= 0; i--) {
        prefix[i] = postfix[i];
    }
    strcat(prefix, "\0");
}


int main() {
    char infix[100];
    char postfix[200];
    char prefix[200];

    // Example Infix expression: A+B*C-D
    strcpy(infix, "A+B*C-D");

    printf("Infix Expression: %s\n", infix);

    // 1. Convert Infix to Postfix
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    // 2. Convert Postfix to Prefix
    infixToPrefix(postfix, prefix);
    printf("Prefix Expression (Prefix Notation): %s\n", prefix);

    return 0;
}