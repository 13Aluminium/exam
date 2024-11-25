#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10

// Function to calculate FIRST set
void calculateFirst(char grammar[MAX][MAX], int n, char first[MAX][MAX]) {
    // Implement FIRST set calculation logic
}

// Function to calculate FOLLOW set
void calculateFollow(char grammar[MAX][MAX], int n, char follow[MAX][MAX]) {
    // Implement FOLLOW set calculation logic
}

// Function to check if grammar is LL(1)
bool isLL1(char grammar[MAX][MAX], int n, char first[MAX][MAX], char follow[MAX][MAX]) {
    // Implement LL(1) condition check
    return true; // Placeholder
}

int main() {
    int n;
    char grammar[MAX][MAX];
    char first[MAX][MAX], follow[MAX][MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter the grammar (Format: A->B|C):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", grammar[i]);
    }

    // Calculate FIRST and FOLLOW sets
    calculateFirst(grammar, n, first);
    calculateFollow(grammar, n, follow);

    // Check if grammar is LL(1)
    if (isLL1(grammar, n, first, follow)) {
        printf("The given grammar is LL(1).\n");
    } else {
        printf("The given grammar is NOT LL(1).\n");
    }

    return 0;
}
