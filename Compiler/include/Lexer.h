#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <FlexLexer.h>
#include <vector>

class Lexer : public FlexLexer{
    std::vector<std::string>& GenerateLexemes(std::string path);
};

#endif