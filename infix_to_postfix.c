#include <stdio.h>
#include <ctype.h>

#define MAX 50

char stack[MAX];
int top = -1;

// Push a value into the stack
void push(char value)
{
    if (top == MAX - 1)
    {
        printf("Stack is full.\n");
        return;
    }
    stack[++top] = value;
}

// Remove the top value from the stack
char pop()
{
    if (top == -1)
    {
        printf("Stack is empty.\n");
        return -1;
    }
    return stack[top--];
}

// See the top value without removing it
char peek()
{
    if (top == -1)
        return -1;
    return stack[top];
}

// Give priority to operators
int precedence(char ch)
{
    if (ch == '^')
        return 3;
    if (ch == '*' || ch == '/')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;
    return 0;
}

int main()
{
    char infix[MAX];
    char postfix[MAX];
    int i = 0, j = 0;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    // Convert infix to postfix
    while (infix[i] != '\0')
    {
        char ch = infix[i];

        // If it is a number or letter, print it directly
        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }
        // If it is an opening bracket, push it to stack
        else if (ch == '(')
        {
            push(ch);
        }
        // If it is a closing bracket, pop until '('
        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
            {
                postfix[j++] = pop();
            }

            // Remove the '(' from the stack
            if (top != -1)
                pop();
        }
        // If it is an operator
        else
        {
            while (top != -1 && peek() != '(' &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }
            push(ch);
        }

        i++;
    }

    // Empty the stack at the end
    while (top != -1)
    {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);
    return 0;
}

/*
Student note:
- Infix form: A + B * C
- Postfix form: A B C * +

How it works:
1. If character is operand -> send to output
2. If '(' -> push to stack
3. If ')' -> pop till '('
4. If operator -> pop higher/equal precedence operators first
5. At end, empty the stack
*/