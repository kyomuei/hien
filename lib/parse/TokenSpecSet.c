#include "parse/TokenSpecSet.h"
#include "hien/parse/tokenize/Lexeme.h"
#include "hien/syntax/Keyword.h"
#include "hien/syntax/TokenKind.h"
#include "parse/TokenSpec.h"

static TokenSpec_t prepareForKeywordMatch(Lexeme_t lexeme) {
    TokenSpec_t spec = { .tokenKind = lexeme.kind, .keyword = MAX_KEYWORD };
    if (lexeme.kind == TOKENKIND_KEYWORD) {
        spec.keyword = Keyword_lookup(Lexeme_tokenText(lexeme));
    }
    return spec;
}

ExpressionStart_t ExpressionStart_lookup(Lexeme_t lexeme) {
    TokenSpec_t spec = prepareForKeywordMatch(lexeme);
    if (TokenSpec_matches(TokenSpec_token(TOKENKIND_INTEGER_LITERAL), spec.tokenKind, spec.keyword)) {
        return EXPRSTART_INTEGERLITERAL;
    }

    return MAX_EXPRSTART;
}

TokenSpec_t ExpressionStart_spec(ExpressionStart_t self) {
    switch (self) {
    case EXPRSTART_INTEGERLITERAL:
        return TokenSpec_token(TOKENKIND_INTEGER_LITERAL);
    default:
        return TokenSpec_token(MAX_TOKENKIND);
    }
}
