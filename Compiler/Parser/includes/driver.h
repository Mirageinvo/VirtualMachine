#ifndef COMPILER_PARSER_INCLUDES_DRIVER
#define COMPILER_PARSER_INCLUDES_DRIVER

#include "../../../build/grammar.tab.hh"
#include <FlexLexer.h>

namespace yy {

class Driver final {
public:
    Driver() = delete;
    Driver(FlexLexer* plex) : plex_(plex) {}
    Driver(const Driver&) = delete;
    Driver(Driver&&) = delete;
    Driver& operator=(const Driver&) = delete;
    Driver& operator=(Driver&&) = delete;

    bool parse() {
        parser prsr(this);
        bool res = prsr.parse();
        return !res;
    }
    parser::token_type yylex(parser::semantic_type* yylval) {
        parser::token_type tt = static_cast<parser::token_type>(plex_->yylex());
        if (tt == parser::token_type::NUMBER) {
            yylval->as<int>() = std::stoi(plex_->YYText());
        }
        return tt;
    }

private:
    FlexLexer* plex_;
};

} //namespace yy

#endif //COMPILER_PARSER_INCLUDES_DRIVER