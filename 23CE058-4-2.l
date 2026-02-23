%{
#include <stdio.h>
%}

%%
[Cc][Hh][Aa][Rr][Uu][Ss][Aa][Tt]   { printf("university"); }
\n                                 { printf("\n"); return 0; }
.                                  { printf("%s", yytext); }
%%

int main() {
    yylex();
    return 0;
}
