#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

void eliminateLeftRecursion(char *nonTerm, char prods[][MAX], int count) {
    char alpha[MAX][MAX], beta[MAX][MAX];
    int alphaCount = 0, betaCount = 0;

    for (int i = 0; i < count; i++) {
        if (prods[i][0] == nonTerm[0]) {  // Left recursion
            strcpy(alpha[alphaCount++], prods[i] + 1);  // Ignore the first char (non-terminal)
        } else {
            strcpy(beta[betaCount++], prods[i]);
        }
    }

    if (alphaCount > 0) {  // Left recursion exists
        printf("%s -> ", nonTerm);
        for (int i = 0; i < betaCount; i++) {
            printf("%s%s' ", beta[i], nonTerm);
            if (i < betaCount - 1) printf("| ");
        }
        printf("\n");

        printf("%s' -> ", nonTerm);
        for (int i = 0; i < alphaCount; i++) {
            printf("%s%s' ", alpha[i], nonTerm);
            if (i < alphaCount - 1) printf("| ");
        }
        printf("ε\n");
    } else {  // No left recursion
        printf("%s -> ", nonTerm);
        for (int i = 0; i < count; i++) {
            printf("%s ", prods[i]);
            if (i < count - 1) printf("| ");
        }
        printf("\n");
    }
}

void eliminateLeftFactoring(char *nonTerm, char prods[][MAX], int count) {
    char common[MAX] = {0}, newProds[MAX][MAX], temp[MAX];
    int len = strlen(prods[0]), found = 0, newProdCount = 0;

    for (int i = 1; i < count; i++) {
        for (int j = 0; j < len; j++) {
            if (prods[0][j] != prods[i][j]) {
                len = j;
                break;
            }
        }
    }

    strncpy(common, prods[0], len);
    common[len] = '\0';

    if (len > 0) {
        printf("%s -> %s%s'\n", nonTerm, common, nonTerm);
        for (int i = 0; i < count; i++) {
            if (strncmp(prods[i], common, len) == 0) {
                strcpy(temp, prods[i] + len);
                if (strlen(temp) == 0) strcpy(temp, "ε");
                strcpy(newProds[newProdCount++], temp);
            } else {
                strcpy(newProds[newProdCount++], prods[i]);
            }
        }

        printf("%s' -> ", nonTerm);
        for (int i = 0; i < newProdCount; i++) {
            printf("%s ", newProds[i]);
            if (i < newProdCount - 1) printf("| ");
        }
        printf("\n");
    } else {
        printf("%s -> ", nonTerm);
        for (int i = 0; i < count; i++) {
            printf("%s ", prods[i]);
            if (i < count - 1) printf("| ");
        }
        printf("\n");
    }
}

int main() {
    char nonTerm[MAX];
    char prods[MAX][MAX];
    int choice, count;

    printf("Enter the non-terminal: ");
    scanf("%s", nonTerm);

    printf("Enter the number of productions for %s: ", nonTerm);
    scanf("%d", &count);

    printf("Enter the productions (one per line):\n");
    for (int i = 0; i < count; i++) {
        scanf("%s", prods[i]);
    }

    printf("\nChoose an operation:\n1. Eliminate Left Recursion\n2. Eliminate Left Factoring\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            eliminateLeftRecursion(nonTerm, prods, count);
            break;
        case 2:
            eliminateLeftFactoring(nonTerm, prods, count);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}
