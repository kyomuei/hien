#pragma once

#include "hien/util/RawBuffer.h"
#include <stdbool.h>

typedef struct SyntaxText_t {
    RawBuffer_t buffer;
} SyntaxText_t;

SyntaxText_t SyntaxText_init(RawBuffer_t buffer);

SyntaxText_t SyntaxText_fromLiteral(char const *literal);

SyntaxText_t SyntaxText_fromPointer(void const *baseAddress, int count);

char const * SyntaxText_baseAddress(SyntaxText_t self);

int SyntaxText_count(SyntaxText_t self);

SyntaxText_t SyntaxText_empty();

bool SyntaxText_isEmpty(SyntaxText_t self);

bool SyntaxText_equals(SyntaxText_t lhs, SyntaxText_t rhs);
