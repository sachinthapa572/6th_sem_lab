#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;
int tempVar = 1;

void push(char ch) { stack[++top] = ch; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Convert infix to postfix
void infixToPostfix(const char *infix, char *postfix)
{
    int i = 0, k = 0;
    char ch;
    while ((ch = infix[i++]) != '\0')
    {
        if (isalnum(ch))
        {
            postfix[k++] = ch;
        }
        else if (ch == '(')
        {
            push(ch);
        }
        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        }
        else
        {
            while (top != -1 && precedence(peek()) >= precedence(ch))
                postfix[k++] = pop();
            push(ch);
        }
    }
    while (top != -1)
        postfix[k++] = pop();
    postfix[k] = '\0';
}

// Generate three-address code from postfix
void generate3AC(const char *postfix)
{
    char stack2[MAX][MAX];
    int top2 = -1;
    char temp[MAX];

    for (int i = 0; postfix[i]; i++)
    {
        if (isalnum(postfix[i]))
        {
            char str[2] = {postfix[i], '\0'};
            strcpy(stack2[++top2], str);
        }
        else
        {
            char op2[MAX], op1[MAX];
            strcpy(op2, stack2[top2--]);
            strcpy(op1, stack2[top2--]);
            sprintf(temp, "t%d", tempVar++);
            printf("%s = %s %c %s\n", temp, op1, postfix[i], op2);
            strcpy(stack2[++top2], temp);
        }
    }
}

int main()
{
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("\nThree-address code:\n");
    generate3AC(postfix);
    return 0;
}
