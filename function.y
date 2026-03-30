%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token TYPE ID NUM

%%

S : TYPE ID '(' PARAMS ')' '{' BODY '}'
    { printf("Valid function definition\n"); }
  ;

PARAMS : PARAM ',' PARAMS
       | PARAM
       | /* empty */
       ;

PARAM : TYPE ID
      ;

BODY : STMT BODY
     | /* empty */
     ;

STMT : TYPE ID '=' NUM ';'
     ;

%%

void yyerror(const char *s) {
    printf("Invalid function definition\n");
}

int main() {
    printf("Enter function definition:\n");
    yyparse();
    return 0;
}