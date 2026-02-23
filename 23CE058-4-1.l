%{
#include <stdio.h>
%}

%%
[0-9]+    { printf("%s\n", yytext); }
\n        { return 0; }
.         { /* ignore other characters */ }
%%

int main() {
    yylex();
    return 0;
}
