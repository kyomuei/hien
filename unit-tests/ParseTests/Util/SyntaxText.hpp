#pragma once

#include <ostream>
#include <string>

extern "C" {

#include "hien/syntax/SyntaxText.h"

}

struct _SyntaxText {
    SyntaxText_t raw;

    _SyntaxText(SyntaxText_t raw) : raw(raw) {};

    _SyntaxText(std::string str) {
        raw = SyntaxText_fromPointer(str.c_str(), str.size());
    }

    bool operator==(const _SyntaxText &other) {
        return SyntaxText_equals(raw, other.raw);
    }
};

static std::ostream& operator <<(std::ostream& os, const _SyntaxText& text) {
    return os << std::string(SyntaxText_baseAddress(text.raw), SyntaxText_count(text.raw));
}
