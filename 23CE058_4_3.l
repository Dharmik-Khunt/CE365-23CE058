%{
#include <stdio.h>

int chars = 0;
int words = 0;
int lines = 0;
int last_char_newline = 0;

int yylex(void);
extern FILE *yyin;
%}

%%
\n              { lines++; chars++; last_char_newline = 1; }
[ \t]+          { chars += yyleng; last_char_newline = 0; }
[^ \t\n]+       { words++; chars += yyleng; last_char_newline = 0; }
%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s input.txt\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    yylex();

    /* FIX: if file does not end with newline */
    if (chars > 0 && last_char_newline == 0) {
        lines++;
        chars++;   /* count missing newline character */
    }

    printf("Characters : %d\n", chars);
    printf("Words : %d\n", words);
    printf("Line : %d\n", lines);

    fclose(yyin);
    return 0;
}
