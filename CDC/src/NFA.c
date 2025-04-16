
// Write a program that constructs the NFA that ends with 'ab'`.

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_STATES 3

enum State
{
    Q0,
    Q1,
    Q2
};

// Function to simulate the NFA
bool accepts(const char *input)
{
    int len = strlen(input);
    bool current_st[MAX_STATES] = {false};
    bool nxt_st[MAX_STATES] = {false};

    current_st[Q0] = true;

    for (int i = 0; i < len; i++)
    {
        char symbol = input[i];

        // Reset nxt_st
        for (int s = 0; s < MAX_STATES; s++)
            nxt_st[s] = false;

        for (int s = 0; s < MAX_STATES; s++)
        {
            if (!current_st[s])
                continue;

            switch (s)
            {
            case Q0:
                if (symbol == 'a')
                {
                    nxt_st[Q0] = true;
                    nxt_st[Q1] = true;
                }
                else if (symbol == 'b')
                {
                    nxt_st[Q0] = true;
                }
                break;
            case Q1:
                if (symbol == 'b')
                {
                    nxt_st[Q2] = true;
                }
                break;
            case Q2:
                // No transitions from Q2
                break;
            }
        }

        // Update current_st
        for (int s = 0; s < MAX_STATES; s++)
        {
            current_st[s] = nxt_st[s];
        }
    }

    return current_st[Q2];
}

int main()
{
    const char *test_strings[] = {
        "a", "b", "ab", "aba", "babab", "baa", ""};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++)
    {
        printf("%-7s -> %s\n", test_strings[i],
               accepts(test_strings[i]) ? "Accepted" : "Rejected");
    }

    return 0;
}
