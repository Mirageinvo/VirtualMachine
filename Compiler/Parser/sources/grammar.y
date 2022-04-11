%language "c++"

%skeleton "lalr1.cc"
%defines
%define api.value.type variant
%param {yy::Driver* driver}

%code requires {
    #include <iostream>
    #include <string>

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
%nterm <int> equals
%nterm <int> expr

%left '+' '-'

%start program

%%

program: eqlist
;

eqlist: equals SCOLON eqlist
      | %empty
;

equals: expr ASSIGN expr       { 
                                $$ = ($1 == $3); 
                                std::cout << "Checking: " << $1 << " vs " << $3 
                                          << "; Result: " << $$
                                          << std::endl; 
                              }
;

expr: expr PLUS expr          { $$ = $1 + $3; }
    | expr MINUS expr         { $$ = $1 - $3; }
    | NUMBER                  { $$ = $1; }
;

%%

namespace yy {

parser::token_type yylex(parser::semantic_type* yylval,                         
                         Driver* driver)
{
  return driver->yylex(yylval);
}

void parser::error(const std::string&){}

}