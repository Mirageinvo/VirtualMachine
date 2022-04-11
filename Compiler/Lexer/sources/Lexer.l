/*%option yyclass = "Lexer"*/
%option c++

%{
//#include "lexer.h" // for future
#include "grammar.tab.hh"
%}

WS                  [ \t\v\n]+
ONE_LINE_COMMENT    "//".*
MULTI_LINE_COMMENT  "/*"(.|\n)*"*/"
DIGIT               [0-9]
DIGIT1              [1-9]
NUMBER              {DIGIT1}{DIGIT}*
FLOAT               {NUMBER}"."{DIGIT}+
ID                  [a-zA-Z]+([0-9]|_|[a-zA-Z])*
LEGAL_SYM           [#\;\{\}\(\)]
QUOTE               [']
DQUOTE              ["]

%%

{WS}                      /*skip blanks and tabs*/

"+"               { return yy::parser::token_type::PLUS;  }
"-"               { return yy::parser::token_type::MINUS; }
"*"               { return yy::parser::token_type::MUL;   }
"/"               { return yy::parser::token_type::DIV;   }
"%"               { return yy::parser::token_type::MOD;   }

"="               { return yy::parser::token_type::ASSIGN; }
"=="              { return yy::parser::token_type::EQUAL;  }
"!="              { return yy::parser::token_type::NEQUAL; }
">"               { return yy::parser::token_type::GRTR;   }
"<"               { return yy::parser::token_type::LESS;   }
">="              { return yy::parser::token_type::GRTREQ; }
"<="              { return yy::parser::token_type::LESSEQ; }
"||"              { return yy::parser::token_type::OR;     }
"&&"              { return yy::parser::token_type::AND;    }

"."               { return yy::parser::token_type::DOT;     }
","               { return yy::parser::token_type::COMMA;   }
":"               { return yy::parser::token_type::COLON;   }
";"               { return yy::parser::token_type::SCOLON;  }
"("               { return yy::parser::token_type::LBR;     }
")"               { return yy::parser::token_type::RBR;     }
"["               { return yy::parser::token_type::LSQBR;   }
"]"               { return yy::parser::token_type::RSQBR;   }
"{"               { return yy::parser::token_type::LCURLBR; }
"}"               { return yy::parser::token_type::RCURLBR; }

"if"              { return yy::parser::token_type::IF;    }
"else"            { return yy::parser::token_type::ELSE;  }
"while"           { return yy::parser::token_type::WHILE; }
"print"           { return yy::parser::token_type::PRINT; }
"?"               { return yy::parser::token_type::SCAN;  }

{DIGIT1}{DIGIT}*  { return yy::parser::token_type::NUMBER; }

%%