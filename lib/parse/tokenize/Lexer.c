#include "hien/parse/tokenize/Lexer.h"

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/syntax/Keyword.h"
#include "hien/syntax/SyntaxText.h"
#include "hien/syntax/TokenKind.h"
#include "hien/syntax/SourceBuffer.h"
#include "hien/util/Range.h"
#include "parse/tokenize/CharacterClass.h"
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

typedef struct LexResult_t {
    TokenKind_t kind;
    Keyword_t keyword;
    int textLength;
} LexResult_t;

static int lexTrivia(SourceBuffer_t cursor);
static LexResult_t lexIntegerLiteral(SourceBuffer_t cursor);
static LexResult_t lexIdentifier(SourceBuffer_t cursor);

static void Lexer_lexNextToken(Lexer_t *self) {

    if (self->nextToken.kind == TOKENKIND_END_OF_FILE) {
        return;
    }

    if (SourceBuffer_isEmpty(self->cursor)) {
        self->nextToken = Lexeme_init(TOKENKIND_END_OF_FILE, "", 0);
        return;
    }

    int triviaLength = lexTrivia(self->cursor);
    self->cursor = SourceBuffer_skip(self->cursor, triviaLength);

    char const *start = SourceBuffer_baseAddress(self->cursor);
    LexResult_t result = {
        .kind = TOKENKIND_UNKNOWN,
        .textLength = 1,
    };

    switch (*start) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        result = lexIntegerLiteral(self->cursor);
        break;
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z':
        result = lexIdentifier(self->cursor);
        break;
    case '\0':
        result = (LexResult_t) {
            .kind = TOKENKIND_END_OF_FILE,
            .textLength = 0,
        };
        break;
    default:
        break;
    }

    self->cursor = SourceBuffer_skip(self->cursor, result.textLength);
    self->nextToken = Lexeme_init(result.kind, start, result.textLength);
}

static int lexTrivia(SourceBuffer_t cursor) {
    assert(!SourceBuffer_isEmpty(cursor));
    char const *base = SourceBuffer_baseAddress(cursor);
    FOR_IN_RANGE(offset, Range_init(0, SourceBuffer_count(cursor))) {
        if (base[offset] != ' ') {
            return offset;
        }
    }

    return SourceBuffer_count(cursor);
}

static LexResult_t lexIntegerLiteral(SourceBuffer_t cursor) {
    char const *base = SourceBuffer_baseAddress(cursor);
    assert(Char_isDigit(*base));

    FOR_IN_RANGE(offset, Range_init(0, SourceBuffer_count(cursor))) {
        if (!Char_isDigit(base[offset])) {
            return (LexResult_t) {
                .kind = TOKENKIND_INTEGER_LITERAL,
                .textLength = offset
            };
        }
    }

    return (LexResult_t) {
        .kind = TOKENKIND_INTEGER_LITERAL,
        .textLength = SourceBuffer_count(cursor),
    };
}

static LexResult_t lexIdentifier(SourceBuffer_t cursor) {
    char const *base = SourceBuffer_baseAddress(cursor);
    assert(Char_isValidIdentifierStart(*base));

    int length = SourceBuffer_count(cursor);
    FOR_IN_RANGE(offset, Range_init(0, SourceBuffer_count(cursor))) {
        if (!Char_isValidIdentifierContinuation(base[offset])) {
            length = offset;
            break;
        }
    }

    TokenKind_t kind = TOKENKIND_IDENTIFIER;
    Keyword_t keyword = Keyword_lookup(SyntaxText_fromPointer(base, length));
    if (keyword != MAX_KEYWORD) {
        kind = TOKENKIND_KEYWORD;
    }

    return (LexResult_t) {
        .kind = kind,
        .keyword = keyword,
        .textLength = length,
    };
}
