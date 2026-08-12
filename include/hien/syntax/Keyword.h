#pragma once

#include "hien/syntax/SyntaxText.h"
typedef enum Keyword_t {
    KEYWORD_RETURN,

    MAX_KEYWORD
} Keyword_t;

Keyword_t Keyword_lookup(SyntaxText_t text);
