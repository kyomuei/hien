#include "hien/util/RawBuffer.h"

#include "hien/util/Range.h"
#include <assert.h>
#include <string.h>

RawBuffer_t RawBuffer_init(void const *baseAddress, int count) {
    assert(count == 0 || baseAddress != NULL);
    return (RawBuffer_t) { .baseAddress = baseAddress, .count = baseAddress != NULL ? count : 0 };
}

RawBuffer_t RawBuffer_empty() {
    return (RawBuffer_t) { .baseAddress = NULL, .count = 0 };
}

bool RawBuffer_isEmpty(RawBuffer_t self) {
    return self.count == 0 || self.baseAddress == NULL;
}

bool RawBuffer_equals(RawBuffer_t lhs, RawBuffer_t rhs) {
    if (lhs.count != rhs.count) { return false; }
    return memcmp(lhs.baseAddress, rhs.baseAddress, lhs.count) == 0;
}

RawBuffer_t RawBuffer_slice(RawBuffer_t self, Range_t range) {
    assert(0 <= range.lowerBound && range.upperBound <= self.count);
    return RawBuffer_init(self.baseAddress + range.lowerBound, range.upperBound - range.lowerBound);
}
