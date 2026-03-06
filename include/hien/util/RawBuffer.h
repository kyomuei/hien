#pragma once

#include "hien/util/Range.h"
#include <stdbool.h>

typedef struct RawBuffer_t {
    void const *baseAddress;
    int count;
} RawBuffer_t;

RawBuffer_t RawBuffer_init(void const *baseAddress, int count);

RawBuffer_t RawBuffer_empty();

bool RawBuffer_isEmpty(RawBuffer_t self);

bool RawBuffer_equals(RawBuffer_t lhs, RawBuffer_t rhs);

RawBuffer_t RawBuffer_slice(RawBuffer_t self, Range_t range);
