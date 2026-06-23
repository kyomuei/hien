#include <gtest/gtest.h>

#include "ParseTests/Util/TokenKind.hpp"
#include "ParseTests/Util/Lexeme.hpp"
#include "ParseTests/Util/SyntaxText.hpp"

extern "C" {

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/parse/tokenize/Lexer.h"
#include "hien/syntax/SyntaxText.h"
#include "hien/syntax/TokenKind.h"

}

struct LexemeSpec {
    TokenKind_t tokenKind;
    std::string tokenText;
};

class TokenizeTests : public testing::Test {};

static void assertLexemes(std::string source, std::vector<LexemeSpec> expectedLexemes, char const * file, int line);

TEST(TokenizeTests, testEmpty) {
    assertLexemes("", {}, __FILE__, __LINE__);
}

TEST(TokenizeTests, testIntegerLiterals) {
    assertLexemes(
        "1234567890",
        {
            LexemeSpec{ .tokenKind = TOKENKIND_INTEGER_LITERAL, .tokenText = "1234567890" },
        },
        __FILE__, __LINE__
    );
}


static void assertTokens(std::vector<Lexeme_t> actualLexemes, std::vector<LexemeSpec> expectedLexemes, char const * file, int line);

static void assertLexemes(std::string source, std::vector<LexemeSpec> expectedLexemes, char const * file, int line) {
    if (expectedLexemes.empty() || expectedLexemes.back().tokenKind != TOKENKIND_END_OF_FILE) {
        expectedLexemes.push_back(LexemeSpec{ .tokenKind = TOKENKIND_END_OF_FILE, .tokenText = "" });
    }

    SyntaxText_t sourceText = SyntaxText_fromPointer(source.c_str(), source.size());
    std::vector<Lexeme_t> lexemes{};
    Lexer_t lexer = Lexer_init(sourceText.buffer);

    while (true) {
        Lexeme_t lexeme = Lexer_advance(&lexer);
        lexemes.push_back(lexeme);

        if (lexeme.kind == TOKENKIND_END_OF_FILE) {
            break;
        }
    }

    assertTokens(lexemes, expectedLexemes, file, line);
}

static void assertTokens(std::vector<Lexeme_t> actualLexemes, std::vector<LexemeSpec> expectedLexemes, char const * file, int line) {

    if (actualLexemes.size() != expectedLexemes.size()) {
        std::stringstream message;
        for (auto lexeme : actualLexemes) {
            message
                << _TokenKind::description(lexeme.kind)
                << ' '
                << _Lexeme(lexeme).tokenText()
                << '\n';
        }

        ADD_FAILURE_AT(file, line)
            << "Expected " << expectedLexemes.size() << " tokens "
            << "but got " << actualLexemes.size() << ":\n"
            << message.str();
        
        return;
    }

    for (int i = 0; i < actualLexemes.size(); i++) {
        auto actual = actualLexemes.at(i);
        auto expected = expectedLexemes.at(i);

        if (actual.kind != expected.tokenKind) {
            ADD_FAILURE_AT(file, line)
                << "Expected token kind " << _TokenKind::description(expected.tokenKind)
                << " but got " << _TokenKind::description(actual.kind) << '\n';
            return;
        }

        if (!(_Lexeme(actual).tokenText() == _SyntaxText(expected.tokenText))) {
            ADD_FAILURE_AT(file, line)
                << "Token text does not match\n"
                << "  expected: " << expected.tokenText << '\n'
                << "  actual:   " << _Lexeme(actual).tokenText() << '\n';
            return;
        }
    }
}
