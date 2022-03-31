#include "Lexer.h"
#include <iostream>
#include <fstream>

int yyFlexLexer::yywrap() {
    return 1;
}

int Lexer::Process(int type){
    lexeme_type_ = type;
    value_ = yytext;
    return 1;
}

int Lexer::ProcessError(){
    lexeme_type_ = ERROR;
    value_ = yytext;
    return 1;
}

void Lexer::GetLexemes(std::vector<std::pair<int, std::string>> *lexemes, const std::string& path){
    std::ifstream in_file(path);
    switch_streams(&in_file, 0);
    while (yylex() != 0){
        (*lexemes).push_back({lexeme_type_, value_});
    }
}
