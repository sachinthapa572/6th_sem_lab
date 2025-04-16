#include <ctype.h>
#include <stdio.h>
#include <string.h>

// 6. Write a program for identifier validation.

int isValidIdentifier(char *str)
{
    if (!isalpha(str[0]) && str[0] != '_')
    {
        return 0;
    }
    for (int i = 1; i < strlen(str); i++)
    {
        if (!isalnum(str[i]) && str[i] != '_')
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char identifier[100];
    printf("Enter an identifier: ");
    scanf("%s", identifier);

    if (isValidIdentifier(identifier))
    {
        printf("'%s' is a valid identifier.\n", identifier);
    }
    else
    {
        printf("'%s' is not a valid identifier.\n", identifier);
    }

    return 0;
}
