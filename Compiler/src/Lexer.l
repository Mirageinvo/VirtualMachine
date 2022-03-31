%option yyclass = "Lexer"
%option c++

%{
#include "Lexer.h"
%}

WS              [ \t\v\n]+
DIGIT           [0-9]
NUMBER          {DIGIT}+
FLOAT           {NUMBER}"."{DIGIT}+
OPERATOR        [+\-\*\/\.\<\>]|"++"|"--"|"+="|"-="|"*="|"\="
ID              [a-zA-Z]+([0-9]|_|[a-zA-Z])*
LEGAL_SYM       [#\;\{\}\(\)]
string_start    ["]([^"\r]|.)*

%%

{WS}                           {}
{NUMBER}                       {return Process(NUMBER); }
{FLOAT}                        {return Process(FLOAT); }
{OPERATOR}                     {return Process(OPERATOR); }
{ID}                           {return Process(ID); }
\"([^\n"])*\"                  {return Process(STRING); }
{LEGAL_SYM}                    {return Process(LEGAL_SYM); }   /* such as #, ;, {, }, (, ) */
.                              {return ProcessError(); }

%%