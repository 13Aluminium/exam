%{
#include <stdio.h>
%}

%%
"<"[^>]*">"     { printf("Tag found: %s\n", yytext); }
.|\n            ; /* Ignore all other characters */

%%

int main() {
    FILE *file;
    file = fopen("tags.txt", "r");
    if (!file) {
        printf("Could not open file tags.txt\n");
        return 1;
    }
    yyin = file;
    yylex();
    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}
