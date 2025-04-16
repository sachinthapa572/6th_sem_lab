// 1. Write a program that constructs the DFA that accepts the language `L = {w | w is a string of a's and b's such that w always starts with 'ab'}`.

#include <stdbool.h>
#include <stdio.h>

typedef enum
{
    START,
    STATE_A,
    STATE_AB,
    REJECT
} State;

int transition(int state, char input)
{
    switch (state)
    {
    case START:
        if (input == 'a')
            return STATE_A;
        break;
    case STATE_A:
        if (input == 'b')
            return STATE_AB;
        else
            return REJECT;
    case STATE_AB:
        if (input == 'a' || input == 'b')
            return STATE_AB;
        break;
    default:
        break;
    }
    return REJECT;
}

bool accepts(const char *input)
{
    int state = START;
    for (int i = 0; input[i] != '\0'; i++)
    {
        state = transition(state, input[i]);
        if (state == REJECT)
            return false;
    }
    return state == STATE_AB;
}

int main()
{
    const char *testStrings[] = {"ab", "aba", "abb", "a", "b", "abab", "abbb", "ba"};
    int numTests = sizeof(testStrings) / sizeof(testStrings[0]);

    for (int i = 0; i < numTests; i++)
    {
        if (accepts(testStrings[i]))
        {
            printf("The string \"%s\" is accepted by the DFA.\n", testStrings[i]);
        }
        else
        {
            printf("The string \"%s\" is rejected by the DFA.\n", testStrings[i]);
        }
    }

    return 0;
}
