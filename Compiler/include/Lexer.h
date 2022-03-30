#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif
#include <vector>

const int OPERATOR = 0;
const int NUMBER = 1;
const int NAME = 2;
const int ERROR = 3;

class Lexer : public yyFlexLexer{
    int lexeme_type_;
    std::string value_;

    int ProcessNumber();
    int ProcessOperator();
    int ProcessName();
    int ProcessError();

  public:
    int yylex() override;
    void GetLexemes(std::vector<std::pair<int, std::string>> *lexemes, const std::string& path);
};

#endif