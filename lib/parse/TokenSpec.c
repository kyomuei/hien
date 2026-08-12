#include "parse/TokenSpec.h"
#include "hien/syntax/Keyword.h"
#include "hien/syntax/TokenKind.h"
#include <assert.h>

TokenSpec_t TokenSpec_token(TokenKind_t token) {
    return (TokenSpec_t) {
        .tokenKind = token,
        .keyword = MAX_KEYWORD,
    };
}

TokenSpec_t TokenSpec_keyword(Keyword_t keyword) {
    return (TokenSpec_t) {
        .tokenKind = TOKENKIND_KEYWORD,
        .keyword = keyword,
    };
}

bool TokenSpec_matches(TokenSpec_t self, TokenKind_t token, Keyword_t keyword) {
    if (self.tokenKind != TOKENKIND_KEYWORD) {
        return self.tokenKind == token;
    }

    assert(self.keyword != MAX_KEYWORD);
    switch (token) {
    case TOKENKIND_KEYWORD:
        return keyword == self.keyword;
    default:
        return false;
    }
}
