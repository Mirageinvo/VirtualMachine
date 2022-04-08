#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include <vector>

enum LexemesTypes: const int{
    OPERATOR,
    NUMBER,
    FLOAT,
    ID,
    STRING,
    LEGAL_SYM,
    ERROR
};

class Lexer : public yyFlexLexer{
public:
    int yylex() override;
    void GetLexemes(std::vector<std::pair<int, std::string>>* lexemes, const std::string& path);

private:
    int lexeme_type_;
    std::string value_;
    int Process(int type);
    int ProcessError();
};

#endif //COMPILER_LEXER_H