%{
#include "function.tab.h"
%}

%option noyywrap

%%
"int"       { return TYPE; }
"float"     { return TYPE; }
"char"      { return TYPE; }

[0-9]+      { return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }

"("         { return '('; }
")"         { return ')'; }
"{"         { return '{'; }
"}"         { return '}'; }
","         { return ','; }
";"         { return ';'; }
"="         { return '='; }

[ \t\n]     ;
.           { return yytext[0]; }
%%