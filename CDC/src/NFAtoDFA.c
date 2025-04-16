#include <stdio.h>
#include <stdlib.h>

#define STATES 10
#define SYMBOLS 2

int nfa[STATES][SYMBOLS][STATES];
int dfa[1 << STATES][SYMBOLS];
int nfa_states, dfa_states = 0;

int is_state_in_set(int *set, int size, int state)
{
    for (int i = 0; i < size; i++)
        if (set[i] == state)
            return 1;
    return 0;
}

int add_state(int *set, int size, int state)
{
    if (!is_state_in_set(set, size, state))
        set[size++] = state;
    return size;
}

int compare_sets(int *a, int a_size, int *b, int b_size)
{
    if (a_size != b_size)
        return 0;
    for (int i = 0; i < a_size; i++)
        if (!is_state_in_set(b, b_size, a[i]))
            return 0;
    return 1;
}

int set_in_dfa_states(int dfa_state_sets[1 << STATES][STATES], int *set, int size)
{
    for (int i = 0; i < dfa_states; i++)
        if (compare_sets(dfa_state_sets[i], STATES, set, size))
            return i;
    return -1;
}

void convert_nfa_to_dfa()
{
    int dfa_state_sets[1 << STATES][STATES] = {0};
    int dfa_set_sizes[1 << STATES] = {0};

    dfa_state_sets[0][0] = 0; // Start with NFA state 0
    dfa_set_sizes[0] = 1;
    dfa_states = 1;

    for (int i = 0; i < dfa_states; i++)
    {
        for (int s = 0; s < SYMBOLS; s++)
        {
            int new_set[STATES] = {0}, new_size = 0;
            for (int j = 0; j < dfa_set_sizes[i]; j++)
            {
                int nfa_state = dfa_state_sets[i][j];
                for (int k = 0; k < STATES; k++)
                {
                    if (nfa[nfa_state][s][k])
                        new_size = add_state(new_set, new_size, k);
                }
            }
            int existing = set_in_dfa_states(dfa_state_sets, new_set, new_size);
            if (existing == -1)
            {
                for (int j = 0; j < new_size; j++)
                    dfa_state_sets[dfa_states][j] = new_set[j];
                dfa_set_sizes[dfa_states] = new_size;
                dfa[i][s] = dfa_states;
                dfa_states++;
            }
            else
            {
                dfa[i][s] = existing;
            }
        }
    }
}

void print_dfa()
{
    printf("\nDFA Transition Table:\n");
    printf("State | 0 | 1\n");
    printf("--------------\n");
    for (int i = 0; i < dfa_states; i++)
        printf("  %d   | %d | %d\n", i, dfa[i][0], dfa[i][1]);
}

int main()
{
    nfa_states = 3;

    // Example NFA
    // State 0 --0--> 0,1
    nfa[0][0][0] = 1;
    nfa[0][0][1] = 1;

    // State 0 --1--> 0
    nfa[0][1][0] = 1;

    // State 1 --1--> 2
    nfa[1][1][2] = 1;

    // State 2 --0--> 2
    nfa[2][0][2] = 1;

    convert_nfa_to_dfa();
    print_dfa();
    return 0;
}
