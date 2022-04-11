#include "driver.h"

int yyFlexLexer::yywrap() { return 1; }

int main(int argc, char** argv) {
    FlexLexer* lexer = new yyFlexLexer;
    yy::Driver driver(lexer);
    driver.parse();
    return 0;
}