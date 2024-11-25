#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

char productions[MAX][MAX];  // Stores the grammar rules
char first[MAX][MAX];        // Stores the First sets
char follow[MAX][MAX];       // Stores the Follow sets
int n;                       // Number of grammar rules

void findFirst(char symbol, int prodIdx);
void findFollow(char symbol, int prodIdx);
int isNonTerminal(char c);
void addUnique(char array[], char element);

int main() {
    int i;

    // Input the grammar
    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions (e.g., A=BC|a):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    // Compute First and Follow sets for all non-terminals
    for (i = 0; i < n; i++) {
        char symbol = productions[i][0];
        findFirst(symbol, i);
        findFollow(symbol, i);
    }

    // Display First sets
    printf("\nFirst Sets:\n");
    for (i = 0; i < n; i++) {
        printf("First(%c) = { %s }\n", productions[i][0], first[i]);
    }

    // Display Follow sets
    printf("\nFollow Sets:\n");
    for (i = 0; i < n; i++) {
        printf("Follow(%c) = { %s }\n", productions[i][0], follow[i]);
    }

    return 0;
}

// Function to find First set
void findFirst(char symbol, int prodIdx) {
    int i, j, k;

    // If already computed, return
    if (first[prodIdx][0] != '\0') return;

    for (i = 2; productions[prodIdx][i] != '\0'; i++) {
        if (isNonTerminal(productions[prodIdx][i])) {
            int idx = -1;

            // Find the index of the production for the non-terminal
            for (j = 0; j < n; j++) {
                if (productions[j][0] == productions[prodIdx][i]) {
                    idx = j;
                    break;
                }
            }

            if (idx != -1) {
                findFirst(productions[prodIdx][i], idx); // Recursive call
                for (k = 0; first[idx][k] != '\0'; k++) {
                    if (first[idx][k] != 'ε') { // Skip epsilon
                        addUnique(first[prodIdx], first[idx][k]);
                    }
                }
            }
        } else {
            addUnique(first[prodIdx], productions[prodIdx][i]); // Terminal
            break;
        }

        if (productions[prodIdx][i] == '|') continue; // Handle OR
    }
}

// Function to find Follow set
void findFollow(char symbol, int prodIdx) {
    int i, j, k, idx;

    // If already computed, return
    if (follow[prodIdx][0] != '\0') return;

    // Start symbol contains $
    if (prodIdx == 0) {
        addUnique(follow[prodIdx], '$');
    }

    for (i = 0; i < n; i++) {
        for (j = 2; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == symbol) {
                if (productions[i][j + 1] != '\0') { // Next symbol exists
                    if (isNonTerminal(productions[i][j + 1])) {
                        idx = -1;

                        // Find production for the next symbol
                        for (k = 0; k < n; k++) {
                            if (productions[k][0] == productions[i][j + 1]) {
                                idx = k;
                                break;
                            }
                        }

                        if (idx != -1) {
                            for (k = 0; first[idx][k] != '\0'; k++) {
                                if (first[idx][k] != 'ε') {
                                    addUnique(follow[prodIdx], first[idx][k]);
                                }
                            }
                        }
                    } else {
                        addUnique(follow[prodIdx], productions[i][j + 1]); // Terminal
                    }
                }

                if (productions[i][j + 1] == '\0' || strchr(first[idx], 'ε')) {
                    if (productions[i][0] != symbol) {
                        findFollow(productions[i][0], i); // Recursive call
                        for (k = 0; follow[i][k] != '\0'; k++) {
                            addUnique(follow[prodIdx], follow[i][k]);
                        }
                    }
                }
            }
        }
    }
}

// Helper to check if a character is a non-terminal
int isNonTerminal(char c) {
    return isupper(c);
}

// Helper to add unique characters to an array
void addUnique(char array[], char element) {
    int i;
    for (i = 0; array[i] != '\0'; i++) {
        if (array[i] == element) return;
    }
    array[i] = element;
    array[i + 1] = '\0';
}