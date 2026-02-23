%{
#include <stdio.h>
#include <string.h>

#define MAX_ERRORS 2000
#define MAX_ERRLEN 256

static int line_no = 1;
static int err_count = 0;
static char errors[MAX_ERRORS][MAX_ERRLEN];

static void add_error(int line, const char *lexeme) {
    if (err_count < MAX_ERRORS) {
        snprintf(errors[err_count], MAX_ERRLEN, "Line %d : %s invalid lexeme", line, lexeme);
        err_count++;
    }
}

static int is_keyword(const char *s) {
    static const char *kw[] = {
        "auto","break","case","char","const","continue","default","do","double","else","enum",
        "extern","float","for","goto","if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"
    };
    for (size_t i = 0; i < sizeof(kw)/sizeof(kw[0]); i++) {
        if (strcmp(s, kw[i]) == 0) return 1;
    }
    return 0;
}
%}

%x CCOMMENT

DIGIT      [0-9]
LETTER     [A-Za-z_]
ID         {LETTER}({LETTER}|{DIGIT})*
INTCONST   {DIGIT}+
FCONST     ({DIGIT}+"."{DIGIT}*)|("."{DIGIT}+)
EXP        [eE][+-]?{DIGIT}+
NUMCONST   ({FCONST}({EXP})?)|({INTCONST}({EXP})?)
WS         [ \t\r]+
CHARCONST  \'(\\.|[^\\\'\n])\'
STRCONST   \"(\\.|[^\\\"\n])*\"

%%

{WS}                                 { }
\n                                   { line_no++; }

"//"[^\n]*                           { }

"/*"                                 { BEGIN(CCOMMENT); }
<CCOMMENT>"*/"                       { BEGIN(INITIAL); }
<CCOMMENT>\n                         { line_no++; }
<CCOMMENT>.                          { }

{DIGIT}+{LETTER}({LETTER}|{DIGIT})*   { add_error(line_no, yytext); }

{STRCONST}                            { printf("String: %s\n", yytext); }
{CHARCONST}                           { printf("Constant: %s\n", yytext); }
{NUMCONST}                            { printf("Constant: %s\n", yytext); }

{ID}                                  { if (is_keyword(yytext)) printf("Keyword: %s\n", yytext); else printf("Identifier: %s\n", yytext); }

"++"|"--"|"+="|"-="|"*="|"/="|"%="|"=="|"!="|"<="|">="|"&&"|"||"|"<<"|">>"|"->"   { printf("Operator: %s\n", yytext); }

"+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"!"|"&"|"|"|"^"|"~"|"?"|":"|"."                   { printf("Operator: %s\n", yytext); }

";"|","|"("|")"|"{"|"}"|"["|"]"                                                  { printf("Punctuation: %s\n", yytext); }

.                                    { add_error(line_no, yytext); }

%%

int yywrap(void) { return 1; }

int main(void) {
    printf("TOKENS\n");
    yylex();

    printf("LEXICAL ERRORS\n");
    if (err_count == 0) printf("None\n");
    else for (int i = 0; i < err_count; i++) printf("%s\n", errors[i]);

    return 0;
}
