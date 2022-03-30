#include "Lexer.h"
#include <iostream>

int yyFlexLexer::yywrap() {
    return 1;
}

int Lexer::ProcessNumber(){
    lexeme_type_ = NUMBER;
    value_ = yytext;
    return 1;
}

int Lexer::ProcessOperator(){
    lexeme_type_ = OPERATOR;
    value_ = yytext;
    return 1;
}

int Lexer::ProcessName(){
    lexeme_type_ = NAME;
    value_ = yytext;
    return 1;
}

int Lexer::ProcessError(){
    lexeme_type_ = ERROR;
    value_ = yytext;
    return 1;
}

void Lexer::GetLexemes(std::vector<std::pair<int, std::string>> *lexemes){
    while (yylex() != 0){
        std::cout << lexeme_type_ << " <" << value_ << ">" << std::endl;
        (*lexemes).push_back({lexeme_type_, value_});
    }
}
