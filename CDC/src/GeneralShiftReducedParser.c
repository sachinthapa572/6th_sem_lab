#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 10
#define MAX_TOKENS 100
#define MAX_LEN 50

typedef struct {
    char lhs[MAX_LEN];  // Left-hand side (e.g., "E")
    char rhs[MAX_LEN];  // Right-hand side (e.g., "E+T")
} Rule;

char stack[MAX_TOKENS][MAX_LEN];
int top = -1;
Rule grammar[MAX_RULES];
int ruleCount = 0;
char expression[MAX_LEN];  // Store the input expression

// Push to stack
void push(char *str) {
    if (top < MAX_TOKENS - 1) {
        strcpy(stack[++top], str);
    }
}

// Pop from stack
void pop() {
    if (top >= 0) {
        top--;
    }
}

// Display stack
void displayStack() {
    for (int i = 0; i <= top; i++) {
        printf("%s", stack[i]);
    }
    printf("\n");
}

// Tokenize user input
void tokenize(char *input, char tokens[MAX_TOKENS][MAX_LEN], int *tokenCount) {
    int i = 0, j = 0, k = 0;

    while (input[i] != '\0') {
        if (isspace(input[i])) {  // Skip spaces
            i++;
            continue;
        }

        if (isalpha(input[i])) {  // Identifier (id)
            tokens[j][k++] = input[i++];
            if (!isalnum(input[i])) { // End of identifier
                tokens[j][k] = '\0';
                j++;
                k = 0;
            }
        } else {  // Operators & Parentheses
            tokens[j][0] = input[i++];
            tokens[j][1] = '\0';
            j++;
        }
    }
    *tokenCount = j;
}

// Ask user for grammar rules
void inputGrammar() {
    printf("Enter number of production rules: ");
    scanf("%d", &ruleCount);
    getchar();  // Consume newline

    for (int i = 0; i < ruleCount; i++) {
        printf("Rule %d (format LHS=RHS, e.g., E=E+T): ", i + 1);
        char buffer[MAX_LEN];
        fgets(buffer, MAX_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline

        char *lhs = strtok(buffer, "=");
        char *rhs = strtok(NULL, "=");
        if (lhs && rhs) {
            strcpy(grammar[i].lhs, lhs);
            strcpy(grammar[i].rhs, rhs);
        } else {
            printf("Invalid rule! Use format: LHS=RHS\n");
            i--; // Re-enter this rule
        }
    }
}

// Apply reductions based on user-defined grammar
void reduce(int *i, int tokenCount, char tokens[MAX_TOKENS][MAX_LEN]) {
    while (1) {
        int reduced = 0;

        for (int r = 0; r < ruleCount; r++) {
            int len = strlen(grammar[r].rhs);
            if (top >= 0 && strcmp(stack[top], grammar[r].rhs) == 0) {
                strcpy(stack[top], grammar[r].lhs);
                printf("%s\t", stack[top]);
                for (int j = *i; j < tokenCount; j++) {
                    printf("%s", tokens[j]);
                }
                printf("\tReduce %s → %s\n", grammar[r].lhs, grammar[r].rhs);
                reduced = 1;
                break;
            }
        }

        if (!reduced) {
            break;
        }
    }
}

int main() {
    inputGrammar();

    printf("\nEnter expression: ");
    fgets(expression, MAX_LEN, stdin);
    expression[strcspn(expression, "\n")] = '\0';

    char tokens[MAX_TOKENS][MAX_LEN];
    int tokenCount = 0;
    tokenize(expression, tokens, &tokenCount);

    // Display the input expression before parsing starts
    printf("\n**Expression:** %s\n", expression);
    printf("**Tokens:** ");
    for (int i = 0; i < tokenCount; i++) {
        printf("%s ", tokens[i]);
    }
    printf("\n\n");

    printf("Stack\tInput\t\tAction\n");
    printf("-----\t------------\t------\n");

    int i = 0;
    while (i < tokenCount) {
        push(tokens[i]);

        printf("%s\t", stack[top]);
        for (int j = i + 1; j < tokenCount; j++) {
            printf("%s", tokens[j]);
        }
        printf("\tShift\n");

        i++;

        reduce(&i, tokenCount, tokens);
    }

    if (top == 0 && strcmp(stack[top], grammar[0].lhs) == 0) {
        printf("\n✅ Expression Accepted!\n");
    } else {
        printf("\n❌ Expression Rejected!\n");
    }

    return 0;
}
