#pragma once

typedef enum TokenKind_t {
    TOKENKIND_UNKNOWN,
    TOKENKIND_INTEGER_LITERAL,
    TOKENKIND_END_OF_FILE,

    MAX_TOKENKIND
} TokenKind_t;
