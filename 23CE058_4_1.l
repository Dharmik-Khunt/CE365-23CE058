%{
#include <stdio.h>
int yylex(void);
%}

%%
[0-9]+      { printf("%s\n", yytext); }
\n          { return 0; }
.           ;
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}
