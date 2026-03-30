%{
#include <stdio.h>
#include <string.h>

int line_no = 1;

/* Symbol Table */
char symtab[100][50];
int symcount = 0;

/* Search identifier in symbol table */
int search(char *id)
{
    int i;
    for(i = 0; i < symcount; i++)
    {
        if(strcmp(symtab[i], id) == 0)
            return 1;
    }
    return 0;
}

/* Insert identifier into symbol table */
void insert(char *id)
{
    if(!search(id))
    {
        strcpy(symtab[symcount], id);
        symcount++;
    }
}
%}

/* Token definitions */
KEYWORD     int|char|float|double|long|short|void|return|struct
ID          [a-zA-Z_][a-zA-Z0-9_]*
NUMBER      [0-9]+(\.[0-9]+)?
CHARCONST   \'[^\']\'
STRING      \"([^\\\"]|\\.)*\"
OPERATOR    \+|\-|\*|\/|=|==|<=|>=|<|>
PUNCT       [\(\)\{\}\[\];,]
INVALID     [0-9]+[a-zA-Z]+

%%

"//".*                                  ;   /* remove single-line comments */
"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"*"+"/"   ;   /* remove multi-line comments */

{KEYWORD}      { printf("Keyword: %s\n", yytext); }
{ID}           { printf("Identifier: %s\n", yytext); insert(yytext); }
{NUMBER}       { printf("Constant: %s\n", yytext); }
{CHARCONST}    { printf("Constant: %s\n", yytext); }
{STRING}       { printf("String: %s\n", yytext); }
{OPERATOR}     { printf("Operator: %s\n", yytext); }
{PUNCT}        { printf("Punctuation: %s\n", yytext); }

{INVALID}      { printf("LEXICAL ERROR at line %d : %s invalid lexeme\n", line_no, yytext); }

\n             { line_no++; }
[ \t]+         ;   /* ignore whitespaces */
.              ;

%%x

int main(int argc, char *argv[])
{
    FILE *fp;
    int i;

    if(argc != 2)
    {
        printf("Usage: ./a.out input.c\n");
        return 0;
    }

    fp = fopen(argv[1], "r");
    if(!fp)
    {
        printf("Cannot open file\n");
        return 0;
    }

    yyin = fp;

    printf("\nTOKENS\n\n");
    yylex();

    printf("\nSYMBOL TABLE ENTRIES\n");
    for(i = 0; i < symcount; i++)
        printf("%d) %s\n", i+1, symtab[i]);

    fclose(fp);
    return 0;
}

int yywrap()
{
    return 1;
}