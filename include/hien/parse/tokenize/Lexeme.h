#pragma once

#include "hien/syntax/TokenKind.h"

typedef struct Lexeme_t {
    TokenKind_t kind;
    int textLength;
    char const *start;
} Lexeme_t;

Lexeme_t Lexeme_init(
    TokenKind_t kind,
    char const *start,
    int textLength
);
