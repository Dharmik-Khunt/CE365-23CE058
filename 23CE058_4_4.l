%{
#include <stdio.h>
#include <string.h>

int lower = 0, upper = 0, digit = 0, symbol = 0;
int length = 0;

int yylex(void);
%}

%%
[a-z]          { lower = 1; length++; }
[A-Z]          { upper = 1; length++; }
[0-9]          { digit = 1; length++; }
[*;#$@]        { symbol = 1; length++; }
\n             { return 0; }
.              { length++; }
%%

int yywrap() {
    return 1;
}

int main() {

    yylex();

    if (length >= 9 && length <= 15 &&
        lower && upper && digit && symbol) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }

    return 0;
}
