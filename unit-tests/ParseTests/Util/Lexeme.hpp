#pragma once

extern "C" {

#include "hien/parse/tokenize/Lexeme.h"

}

#include "./SyntaxText.hpp"

struct _Lexeme {
    Lexeme_t raw;

    _Lexeme(Lexeme_t raw) : raw(raw) {}

    _SyntaxText tokenText() {
        return _SyntaxText(SyntaxText_fromPointer(raw.start, raw.textLength));
    }
};
