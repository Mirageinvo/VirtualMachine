%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires {
    #include <algorithm>
    #include <string>
    #include <vector>

    namespace yy { class Driver; }
}

%code {
    #include "driver.h"
    namespace yy {
        parser::token_type yylex(parser::semantic_type* yylval, Driver* driver);
    }
}

%token
    PLUS    "+"
    MINUS   "-"
    MUL     "*"
    DIV     "/"
    MOD     "%"

    ASSIGN  "="
    EQUAL   "=="
    NEQUAL  "!="
    GRTR    ">"
    LESS    "<"
    GRTREQ  ">="
    LESSEQ  "<="
    OR      "||"
    AND     "&&"

    DOT     "."
    COMMA   ","
    COLON   ":"
    SCOLON  ";"
    LBR     "("
    RBR     ")"
    LSQBR   "["
    RSQBR   "]"
    LCURLBR "{"
    RCURLBR "}"

    IF      "if"
    ELSE    "else"
    WHILE   "while"
    PRINT   "print"
    SCAN    "?"
    
    ERR
;

%token <int> NUMBER
%nterm <std::vector<int>> expr
%nterm <std::pair<std::vector<int>, std::vector<int>>> equals
%nterm <std::vector<std::pair<std::vector<int>, std::vector<int>>>> eqlist

%left '+' '-'

%start program

%%

program: eqlist               { driver->insert($1); }
;

eqlist: equals SCOLON eqlist  { $$ = $3; $$.push_back($1); }
      | equals SCOLON         { $$.push_back($1);          }
;

equals: expr ASSIGN expr       { $$ = std::make_pair($1, $3); }
;

expr: NUMBER                  { $$.push_back($1); }
    | expr PLUS NUMBER        { $$ = $1; $$.push_back($3); }
    | expr MINUS NUMBER       { $$ = $1; $$.push_back(-$3); }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&) {}

}