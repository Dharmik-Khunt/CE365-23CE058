%{
#include <stdio.h>

int characters = 0;
int words = 0;
int lines = 0;
%}

%%
[^\n ]+    { words++; characters += yyleng; }
[ ]        { characters++; }
\n         { lines++; characters++; }
%%

int main() {
    yylex();
    printf("Characters : %d\n", characters);
    printf("Words : %d\n", words);
    printf("Line : %d\n", lines);
    return 0;
}
