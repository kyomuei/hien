#include "parse/tokenize/CharacterClass.h"

bool Char_isDigit(char c) {
    return '0' <= c && c <= '9';
}

bool Char_isValidIdentifierStart(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool Char_isValidIdentifierContinuation(char c) {
    return Char_isValidIdentifierStart(c) || Char_isDigit(c);
}
