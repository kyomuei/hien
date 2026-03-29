#include "hien/syntax/SourceBuffer.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


SourceBuffer_t SourceBuffer_init(char const *baseAddress, int count) {
    assert(count == 0 || baseAddress != NULL);
    return (SourceBuffer_t) {
        .baseAddress = baseAddress,
        .count = baseAddress != NULL ? count : 0,
    };
}

SourceBuffer_t SourceBuffer_empty() {
    return (SourceBuffer_t) {
        .baseAddress = NULL,
        .count = 0
    };
}

char const * SourceBuffer_baseAddress(SourceBuffer_t self) {
    return self.baseAddress;
}

int SourceBuffer_count(SourceBuffer_t self) {
    return self.count;
}

bool SourceBuffer_isEmpty(SourceBuffer_t self) {
    return SourceBuffer_count(self) == 0 || SourceBuffer_baseAddress(self) == NULL;
}

bool SourceBuffer_equals(SourceBuffer_t lhs, SourceBuffer_t rhs) {
    if (SourceBuffer_count(lhs) != SourceBuffer_count(rhs)) {
        return false;
    }
    return memcmp(
        SourceBuffer_baseAddress(lhs),
        SourceBuffer_baseAddress(rhs),
        SourceBuffer_count(lhs)
    ) == 0;
}

char SourceBuffer_get(SourceBuffer_t self, int index) {
    assert(((unsigned int)index) <= SourceBuffer_count(self));
    return SourceBuffer_baseAddress(self)[index];
}

SourceBuffer_t SourceBuffer_skip(SourceBuffer_t self, int count) {
    assert(((unsigned int)count) <= SourceBuffer_count(self));
    return SourceBuffer_init(SourceBuffer_baseAddress(self) + count, SourceBuffer_count(self) - count);
}
