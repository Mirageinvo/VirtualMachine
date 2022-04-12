#ifndef COMPILER_PARSER_INCLUDES_DRIVER
#define COMPILER_PARSER_INCLUDES_DRIVER

#include <numeric>
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

    void insert(std::vector<std::pair<std::vector<int>, std::vector<int>>> v) {
        vvv_.assign(v.rbegin(), v.rend());
    }

  void printout() const {
    for (auto vv : vvv_) {
      int sumleft = std::accumulate(vv.first.begin(), vv.first.end(), 0);
      int sumright = std::accumulate(vv.second.begin(), vv.second.end(), 0);
      int res = (sumleft == sumright);
      std::cout << "Checking: " << sumleft << " vs " << sumright
                << "; Result: " << res << std::endl;
    }
  }

private:
    FlexLexer* plex_;
    std::vector<std::pair<std::vector<int>, std::vector<int>>> vvv_;
};

} //namespace yy

#endif //COMPILER_PARSER_INCLUDES_DRIVER