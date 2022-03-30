%option yyclass = "Lexer"
%option c++

%{
#include "Lexer.h";
%}

WS          [ \t\v\n]+
DIGIT       [0-9]
NUMBER      {DIGIT}+
OPERATOR    [+\-\*\/]
NAME        [a-zA-Z]+[0-9]*

%%

{WS}                           {}
{NUMBER}                       {return ProcessNumber(); }
{OPERATOR}                     {return ProcessOperator(); }
{NAME}                         {return ProcessName(); }
.                              {return ProcessError(); }

%%