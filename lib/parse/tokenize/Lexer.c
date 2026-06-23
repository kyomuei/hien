#include "hien/parse/tokenize/Lexer.h"

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/syntax/TokenKind.h"
#include "hien/syntax/SourceBuffer.h"
#include "hien/util/Range.h"
#include <assert.h>

Lexer_t Lexer_init(SourceBuffer_t source) {
    Lexer_t lexer = (Lexer_t) {
        .source = source,
        .cursor = source,
        .nextToken = Lexeme_init(TOKENKIND_UNKNOWN, "", 0)
    };

    Lexer_advance(&lexer);
    return lexer;
}

static void Lexer_lexNextToken(Lexer_t *self);

Lexeme_t Lexer_advance(Lexer_t *self) {
    Lexeme_t current = self->nextToken;    
    Lexer_lexNextToken(self);
    return current;
}

Lexeme_t Lexer_peek(Lexer_t const *self) {
    return self->nextToken;
}

static int lexIntegerLiteral(SourceBuffer_t cursor);

static void Lexer_lexNextToken(Lexer_t *self) {

    if (self->nextToken.kind == TOKENKIND_END_OF_FILE) {
        return;
    }

    if (SourceBuffer_isEmpty(self->cursor)) {
        self->nextToken = Lexeme_init(TOKENKIND_END_OF_FILE, "", 0);
        return;
    }

    TokenKind_t kind = TOKENKIND_UNKNOWN;
    char const *start = SourceBuffer_baseAddress(self->cursor);
    int length = 1;

    switch (*start) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        length = lexIntegerLiteral(self->cursor);
        kind = TOKENKIND_INTEGER_LITERAL;
        break;
    case '\0':
        kind = TOKENKIND_END_OF_FILE;
        length = 0;
    default:
        break;
    }

    self->cursor = SourceBuffer_skip(self->cursor, length);
    self->nextToken = Lexeme_init(kind, start, length);
}

static int lexIntegerLiteral(SourceBuffer_t cursor) {
    char const *base = SourceBuffer_baseAddress(cursor);
    assert('0' <= *base && *base <= '9');

    FOR_IN_RANGE(offset, Range_init(0, SourceBuffer_count(cursor))) {
        if (!('0' <= base[offset] && base[offset] <= '9')) {
            return offset;
        }
    }

    return SourceBuffer_count(cursor);
}
