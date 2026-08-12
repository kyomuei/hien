#pragma once

#include "hien/syntax/Keyword.h"
#include "hien/syntax/TokenKind.h"
#include <stdbool.h>

typedef struct TokenSpec_t {
    TokenKind_t tokenKind;
    Keyword_t keyword;
} TokenSpec_t;

TokenSpec_t TokenSpec_token(TokenKind_t token);

TokenSpec_t TokenSpec_keyword(Keyword_t keyword);

bool TokenSpec_matches(TokenSpec_t self, TokenKind_t token, Keyword_t keyword);
