#pragma once

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/parse/tokenize/Lexer.h"
#include "hien/syntax/SourceBuffer.h"
#include "hien/syntax/TokenKind.h"
#include <stdbool.h>

typedef struct Parser_t {
    Lexer_t lexer;
    Lexeme_t currentToken;
} Parser_t;

Parser_t Parser_init(SourceBuffer_t source);

bool Parser_isAt(Parser_t const *self, TokenKind_t kind);

void Parser_consumeAnyToken(Parser_t *self);

void Parser_eat(Parser_t *self, TokenKind_t kind);

bool Parser_consumeIf(Parser_t *self, TokenKind_t kind);
