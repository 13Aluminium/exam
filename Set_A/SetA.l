%{
#include <stdio.h>
%}

%%
int|float|double  { printf("Keyword: %s\n", yytext); }
[a-zA-Z][a-zA-Z0-9]* { printf("Identifier: %s\n", yytext); }
[0-9]+(\.[0-9]+)? { printf("Number: %s\n", yytext); }
[ \t\n]+ ;  // Ignore whitespace
. { printf("Unknown: %s\n", yytext); }  // Catch-all for other characters
%%

int main() {
    yylex();
    return 0;
}
int yywrap() {
    return 1;
}
