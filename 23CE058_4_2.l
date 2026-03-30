%{
#include <stdio.h>
int yylex(void);
%}

%%
[Cc][Hh][Aa][Rr][Uu][Ss][Aa][Tt]   { printf("university"); }
\n                                { printf("\n"); return 0; }
.                                 { printf("%s", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0;
}
