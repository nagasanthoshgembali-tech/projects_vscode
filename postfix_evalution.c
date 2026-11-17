#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX 50

int stack[MAX];
int top = -1;

void push(int x)
{
    if (top == MAX - 1)
    {
        printf("Stack Overflow! Cannot push %d\n", x);
        return;
    }
    stack[++top] = x;
}

int pop()
{
    if (top == -1)
    {
        printf("Stack Underflow! Nothing to pop\n");
        return -1;
    }
    return stack[top--];
}

/* converts a letter (upper or lower) into a unique array index 0-51 */
int getIndex(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A'; /* 0 to 25 */
    else
        return (ch - 'a') + 26; /* 26 to 51 */
}

int main()
{
    char postfix[MAX];
    int i = 0, op1, op2, result;
    int values[52]; /* 0-25 = A-Z, 26-51 = a-z */

    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    /* find which letters are used, ask user for their values */
    for (i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];
        if (isalpha(ch))
        {
            printf("Enter value for %c: ", ch);
            scanf("%d", &values[getIndex(ch)]);
        }
    }

    i = 0;
    while (postfix[i] != '\0')
    {
        char ch = postfix[i];

        if (isdigit(ch))
        {
            push(ch - '0');
        }
        else if (isalpha(ch))
        {
            push(values[getIndex(ch)]);
        }
        else
        {
            op2 = pop();
            op1 = pop();

            if (ch == '+')
                result = op1 + op2;
            else if (ch == '-')
                result = op1 - op2;
            else if (ch == '*')
                result = op1 * op2;
            else if (ch == '/')
                result = op1 / op2;
            else if (ch == '^')
                result = (int)pow(op1, op2);

            push(result);
        }
        i++;
    }
    printf("Result = %d\n", pop());
    return 0;
}