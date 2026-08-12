#include "hien/parse/tokenize/Lexeme.h"
#include "hien/syntax/SyntaxText.h"

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

SyntaxText_t Lexeme_tokenText(Lexeme_t self) {
    return SyntaxText_fromPointer(self.start, self.textLength);
}
