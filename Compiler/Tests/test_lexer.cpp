#include "Lexer.h"
#include <gtest/gtest.h>

const std::string texts_path = "../Compiler/Tests/Texts/";

TEST(GetLexemes, ID){
    Lexer lexer;
    std::vector<std::pair<int, std::string>> lexemes;
    lexer.GetLexemes(&lexemes, texts_path + "id_text.txt");

    std::vector<std::pair<int, std::string>> true_lexemes = {
        {ID, "plis_plos"},
        {ID, "qwerty"},
        {OPERATOR, "-"},
        {ID, "iops"},
        {ID, "string"},
    };

    ASSERT_EQ(lexemes, true_lexemes);
}

TEST(GetLexemes, FLOAT){
    Lexer lexer;
    std::vector<std::pair<int, std::string>> lexemes;
    lexer.GetLexemes(&lexemes, texts_path + "float_text.txt");

    std::vector<std::pair<int, std::string>> true_lexemes = {
        {FLOAT, "1234.0987"},
        {FLOAT, "4783.47"},
        {NUMBER, "666"},
        {OPERATOR, "."},
        {ID, "qwerty"},
        {FLOAT, "7.7"}
    };

    ASSERT_EQ(lexemes, true_lexemes);
}

TEST(GetLexemes, STRING){
    Lexer lexer;
    std::vector<std::pair<int, std::string>> lexemes;
    lexer.GetLexemes(&lexemes, texts_path + "strings.txt");

    std::vector<std::pair<int, std::string>> true_lexemes = {
        {STRING, "\"qwerty\""},
        {STRING, "\"\""},
        {STRING, "\"Hello World\\n\""},
        {STRING, "don't\ndo that"}
    };

    for (int i = 0; i < 3; ++i)
    {
        ASSERT_EQ(lexemes[i], true_lexemes[i]);
    }
    ASSERT_NE(lexemes[3], true_lexemes[3]);
}

TEST(GetLexemes, text1){
    Lexer *lexer = new Lexer;
    std::vector<std::pair<int, std::string>> lexemes;
    lexer->GetLexemes(&lexemes, texts_path + "text1.txt");
    delete lexer;

    std::vector<std::pair<int, std::string>> true_lexemes = {
        {ID, "int"},
        {ID, "a"},
        {LEGAL_SYM, ";"},
        {ID, "double"},
        {ID, "b"},
        {OPERATOR, "="},
        {FLOAT, "9.7"},
        {LEGAL_SYM, ";"},
        {ID, "a"},
        {OPERATOR, "++"},
        {LEGAL_SYM, ";"},
        {ID, "a"},
        {OPERATOR, "="},
        {ID, "a"},
        {OPERATOR, "+"},
        {ID, "b"},
        {LEGAL_SYM, ";"},
    };

    ASSERT_EQ(lexemes, true_lexemes);

    lexemes.push_back({10, "l"});
    ASSERT_NE(lexemes, true_lexemes);
}

TEST(GetLexemes, text2){
    Lexer *lexer = new Lexer;
    std::vector<std::pair<int, std::string>> lexemes;
    lexer->GetLexemes(&lexemes, texts_path + "text2.txt");
    delete lexer;

    std::vector<std::pair<int, std::string>> true_lexemes = {
        {LEGAL_SYM, "#"},
        {ID, "include"},
        {OPERATOR, "<"},
        {ID, "stdio"},
        {OPERATOR, "."},
        {ID, "h"},
        {OPERATOR, ">"},
        {ID, "void"},
        {ID, "main"},
        {LEGAL_SYM, "("},
        {LEGAL_SYM, ")"},
        {LEGAL_SYM, "{"},
        {ID, "printf"},
        {LEGAL_SYM, "("},
        {STRING, "\"Hello world\""},
        {LEGAL_SYM, ")"},
        {LEGAL_SYM, ";"},
        {LEGAL_SYM, "}"},
    };

    ASSERT_EQ(lexemes, true_lexemes);

}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
