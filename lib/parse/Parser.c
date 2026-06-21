#include "Parser.h"

#include "hien/parse/tokenize/Lexer.h"
#include "hien/syntax/TokenKind.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

Parser_t Parser_init(SourceBuffer_t source) {
    Parser_t parser = (Parser_t) {
        .lexer = Lexer_init(source),
    };
    parser.currentToken = Lexer_advance(&parser.lexer);

    return parser;
}

bool Parser_isAt(Parser_t const *self, TokenKind_t kind) {
    return self->currentToken.kind == kind;
}

void Parser_consumeAnyToken(Parser_t *self) {
    self->currentToken = Lexer_advance(&self->lexer);
}

void Parser_eat(Parser_t *self, TokenKind_t kind) {
    assert(Parser_isAt(self, kind));
    Parser_consumeAnyToken(self);
}

bool Parser_consumeIf(Parser_t *self, TokenKind_t kind) {
    if (Parser_isAt(self, kind)) {
        Parser_eat(self, kind);
        return true;
    } else {
        return false;
    }
}
