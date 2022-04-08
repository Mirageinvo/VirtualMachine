#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <cassert>

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
    assert(in_file.is_open());
    switch_streams(&in_file, nullptr);
    while (yylex() != 0){
        (*lexemes).push_back({lexeme_type_, value_});
    }
}