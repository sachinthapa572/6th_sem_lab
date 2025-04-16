#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c)
{
    if (top == MAX - 1)
    {
        printf("Error: Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop()
{
    if (top == -1)
    {
        printf("Error: Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int precedence(char c)
{
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return -1;
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Basic validation of infix expression
int isValidInfix(const char *infix)
{
    int len = strlen(infix);
    int paren_count = 0;

    for (int i = 0; i < len; i++)
    {
        if (isspace(infix[i]))
            continue; // Skip spaces
        if (!(isalnum(infix[i]) || isOperator(infix[i]) || infix[i] == '(' || infix[i] == ')'))
        {
            printf("Error: Invalid character '%c'\n", infix[i]);
            return 0;
        }
        if (infix[i] == '(')
            paren_count++;
        if (infix[i] == ')')
            paren_count--;
        if (paren_count < 0)
        {
            printf("Error: Unmatched closing parenthesis\n");
            return 0;
        }
        // Check for consecutive operators
        if (isOperator(infix[i]) && i + 1 < len && isOperator(infix[i + 1]))
        {
            printf("Error: Consecutive operators at position %d\n", i);
            return 0;
        }
    }
    if (paren_count != 0)
    {
        printf("Error: Unmatched opening parenthesis\n");
        return 0;
    }
    return 1;
}

void infixToPostfix(const char *infix, char *postfix)
{
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++)
    {
        if (isspace(infix[i]))
            continue; // Skip  spaces
        if (isalnum(infix[i]))
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[j++] = pop();
            }
            if (top == -1)
            {
                printf("Error: Mismatched parentheses\n");
                exit(1);
            }
            pop(); // Remove '('
        }
        else if (isOperator(infix[i]))
        {
            while (top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(infix[i]))
            {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }
    while (top != -1)
    {
        if (stack[top] == '(')
        {
            printf("Error: Mismatched parentheses\n");
            exit(1);
        }
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main()
{
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    fgets(infix, MAX, stdin);
    infix[strcspn(infix, "\n")] = '\0'; // Remove newline

    if (!isValidInfix(infix))
    {
        printf("Invalid infix expression\n");
        return 1;
    }

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}