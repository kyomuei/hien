#pragma once

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/syntax/SourceBuffer.h"

typedef struct Lexer_t {
    SourceBuffer_t source;
    SourceBuffer_t cursor;
    Lexeme_t nextToken;
} Lexer_t;

Lexer_t Lexer_init(SourceBuffer_t source);

Lexeme_t Lexer_advance(Lexer_t *self);

Lexeme_t Lexer_peek(Lexer_t const *self);
