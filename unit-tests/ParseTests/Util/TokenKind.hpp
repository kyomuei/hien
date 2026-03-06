#pragma once

#include <string>

extern "C" {

#include "hien/syntax/TokenKind.h"

}

struct _TokenKind {
    static std::string description(TokenKind_t kind) {
        switch (kind) {
        case TOKENKIND_UNKNOWN:
            return "unknown";
        case TOKENKIND_INTEGER_LITERAL:
            return "integer-literal";
        case TOKENKIND_END_OF_FILE:
            return "end-of-file";
        default:
            return "invalid";
        }
    }
};
