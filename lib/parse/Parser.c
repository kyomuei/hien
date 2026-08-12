#include "Parser.h"

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/parse/tokenize/Lexer.h"
#include "parse/TokenSpec.h"
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

bool Parser_isAt(Parser_t const *self, TokenSpec_t spec) {
    Lexeme_t lexeme = self->currentToken;
    return TokenSpec_matches(spec, lexeme.kind, Keyword_lookup(Lexeme_tokenText(lexeme)));
}

void Parser_consumeAnyToken(Parser_t *self) {
    self->currentToken = Lexer_advance(&self->lexer);
}

void Parser_eat(Parser_t *self, TokenSpec_t spec) {
    assert(Parser_isAt(self, spec));
    Parser_consumeAnyToken(self);
}

bool Parser_consumeIf(Parser_t *self, TokenSpec_t spec) {
    if (Parser_isAt(self, spec)) {
        Parser_eat(self, spec);
        return true;
    } else {
        return false;
    }
}
