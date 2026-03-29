#pragma once

#include <stdbool.h>

typedef struct SourceBuffer_t {
    char const *baseAddress;
    int count;
} SourceBuffer_t;

SourceBuffer_t SourceBuffer_init(char const *baseAddress, int count);

SourceBuffer_t SourceBuffer_empty();

char const * SourceBuffer_baseAddress(SourceBuffer_t self);

int SourceBuffer_count(SourceBuffer_t self);

bool SourceBuffer_isEmpty(SourceBuffer_t self);

bool SourceBuffer_equals(SourceBuffer_t lhs, SourceBuffer_t rhs);

char SourceBuffer_get(SourceBuffer_t self, int index);

SourceBuffer_t SourceBuffer_skip(SourceBuffer_t self, int count);
