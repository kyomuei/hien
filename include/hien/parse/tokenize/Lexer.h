#pragma once

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/util/RawBuffer.h"

typedef struct Lexer_t {
    RawBuffer_t source;
    RawBuffer_t cursor;
    Lexeme_t nextToken;
} Lexer_t;

Lexer_t Lexer_init(RawBuffer_t source);

Lexeme_t Lexer_advance(Lexer_t *self);

Lexeme_t Lexer_peek(Lexer_t const *self);
