#include "hien/parse/tokenize/Lexeme.h"

Lexeme_t Lexeme_init(
    TokenKind_t kind,
    char const *start,
    int textLength
) {
    return (Lexeme_t) {
        .kind = kind,
        .start = start,
        .textLength = textLength,
    };
}
