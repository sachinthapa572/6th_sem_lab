#include <stdio.h>
#include <string.h>

char input[20] = "id+id*id$";
char stack[40];
int top = -1, i = 0;

void printstack(const char *action)
{
    printf("Stack: %-15s Input: %-10s Action: %s\n", stack, &input[i], action);
}

void replace_id_with_E()
{
    if (top > 0 && stack[top] == 'd' && stack[top - 1] == 'i')
    {
        stack[--top] = 'E'; // Replace 'd' with 'E'
        printstack("REDUCE E → id");
    }
}

void reduce_E_op_E()
{
    while (1)
    {
        if (top >= 2 && stack[top - 2] == 'E' && (stack[top - 1] == '+' || stack[top - 1] == '*') && stack[top] == 'E')
        {
            top -= 2; // remove op and E
            stack[top] = 'E';
            stack[top + 1] = '\0';
            printstack("REDUCE E → E op E");
        }
        else
            break;
    }
}

int main()
{
    printf("SHIFT-REDUCE PARSER\nInput: %s\n\n", input);
    printf("%-20s %-15s %s\n", "Stack", "Input", "Action");

    while (input[i] != '\0')
    {
        if (input[i] == 'i' && input[i + 1] == 'd')
        {
            stack[++top] = 'i';
            stack[++top] = 'd';
            stack[top + 1] = '\0';
            printstack("SHIFT id");
            i += 2;
            replace_id_with_E();
            reduce_E_op_E();
        }
        else if (input[i] == '+' || input[i] == '*')
        {
            stack[++top] = input[i++];
            stack[top + 1] = '\0';
            printstack("SHIFT operator");
        }
        else if (input[i] == '$')
        {
            reduce_E_op_E();
            if (strcmp(stack, "E") == 0)
            {
                printstack("ACCEPT");
            }
            else
            {
                printstack("ERROR");
            }
            break;
        }
        else
        {
            printstack("ERROR");
            break;
        }
    }

    return 0;
}
