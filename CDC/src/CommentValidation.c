//  Write a program for `comment validation`.
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isValidComment(const char *comment)
{
    int len = strlen(comment);
    char mdcstr[len + 1];
    strcpy(mdcstr, comment);

    // trim the comment
    char *start = mdcstr;
    while (isspace((unsigned char)*start))
    {
        start++;
    }

    char *end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end))
    {
        *end = '\0';
        end--;
    }

    if (start[0] == '/' && start[1] == '/')
    {
        return true;
    }
    else if (len >= 4 && start[0] == '/' && start[1] == '*' && end[0] == '/' && end[-1] == '*')
    {
        return true;
    }
    return false;
}

int main()
{
    char comment[100];
    printf("Enter a comment: ");
    fgets(comment, sizeof(comment), stdin);
    comment[strcspn(comment, "\n")] = '\0';

    if (isValidComment(comment))
    {
        printf("It's Valid comment\n");
    }
    else
    {
        printf("It's Invalid comment\n");
    }

    return 0;
}
