#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAG_LENGTH 100

// Function to check if a character is part of an HTML tag
bool isTagStart(char c) {
    return c == '<';
}

// Function to check if a character is the end of an HTML tag
bool isTagEnd(char c) {
    return c == '>';
}

// Function to extract HTML tags from a file
void extractHTMLTags(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char ch;
    char tag[MAX_TAG_LENGTH];
    int index = 0;
    bool insideTag = false;

    printf("Extracted HTML tags:\n");
    while ((ch = fgetc(file)) != EOF) {
        if (isTagStart(ch)) {
            insideTag = true;
            index = 0;
            tag[index++] = ch; // Start of tag
        } else if (insideTag) {
            tag[index++] = ch;
            if (isTagEnd(ch)) {
                insideTag = false;
                tag[index] = '\0'; // Null-terminate the tag
                printf("%s\n", tag);
            }
        }
    }

    fclose(file);
}

int main() {
    char filename[100];
    printf("Enter the file name: ");
    scanf("%s", filename);

    extractHTMLTags(filename);

    return 0;
}