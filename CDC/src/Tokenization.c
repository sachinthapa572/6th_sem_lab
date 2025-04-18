#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *keywords[] = {"int", "float", "if", "else", "while", "for", "return"};
const int num_keywords = 7;

const char *operators = "+-*/=";

const char *special_symbols = "{}();,";

int is_keyword(const char *str)
{
    for (int i = 0; i < num_keywords; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int is_operator(char ch)
{
    for (int i = 0; operators[i] != '\0'; i++)
    {
        if (ch == operators[i])
        {
            return 1;
        }
    }
    return 0;
}

int is_special_symbol(char ch)
{
    for (int i = 0; special_symbols[i] != '\0'; i++)
    {
        if (ch == special_symbols[i])
        {
            return 1;
        }
    }
    return 0;
}

void tokenize(const char *input)
{
    int i = 0;
    char token[100];

    while (input[i] != '\0')
    {
        while (isspace(input[i]))
        {
            i++;
        }

        if (input[i] == '\0')
            break;

        int token_pos = 0;

        if (isalpha(input[i]) || input[i] == '_')
        {
            token[token_pos++] = input[i++];
            while (isalnum(input[i]) || input[i] == '_')
            {
                token[token_pos++] = input[i++];
            }
            token[token_pos] = '\0';

            if (is_keyword(token))
            {
                printf("Keyword: %s\n", token);
            }
            else
            {
                printf("Identifier: %s\n", token);
            }
        }
        else if (isdigit(input[i]))
        {
            token[token_pos++] = input[i++];
            while (isdigit(input[i]) || input[i] == '.')
            {
                token[token_pos++] = input[i++];
            }
            token[token_pos] = '\0';
            printf("Number: %s\n", token);
        }
        else if (is_operator(input[i]))
        {
            token[0] = input[i];
            token[1] = '\0';
            printf("Operator: %c\n", input[i]);
            i++;
        }
        else if (is_special_symbol(input[i]))
        {
            token[0] = input[i];
            token[1] = '\0';
            printf("Special Symbol: %c\n", input[i]);
            i++;
        }
        else
        {
            printf("Invalid character: %c\n", input[i]);
            i++;
        }
    }
}

int main()
{
    const char *code = "int main() { int a = 5; if (a == 5) return a; }";
    printf("\nTokenized Output:\n");
    tokenize(code);

    return 0;
}
