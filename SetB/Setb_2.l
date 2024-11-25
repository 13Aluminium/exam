%{
#include <stdio.h>
%}

%%

[0-9]+                { printf("Number: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }
[+\-*/=()]            { printf("Operator: %s\n", yytext); }
[ \t\n]               { /* Ignore whitespace */ }
.                     { printf("Invalid character: %s\n", yytext); }

%%

int main() {
    printf("Enter an arithmetic expression: ");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}