#include "hien/syntax/SyntaxText.h"

#include "hien/util/RawBuffer.h"
#include <stdbool.h>
#include <string.h>

SyntaxText_t SyntaxText_init(RawBuffer_t buffer) {
    return (SyntaxText_t) { .buffer = buffer };
}

SyntaxText_t SyntaxText_fromLiteral(char const *literal) {
    return SyntaxText_fromPointer(literal, strlen(literal));
}

SyntaxText_t SyntaxText_fromPointer(void const *baseAddress, int count) {
    return SyntaxText_init(RawBuffer_init(baseAddress, count));
}

char const * SyntaxText_baseAddress(SyntaxText_t self) {
    return self.buffer.baseAddress;
}

int SyntaxText_count(SyntaxText_t self) {
    return self.buffer.count;
}

SyntaxText_t SyntaxText_empty() {
    return SyntaxText_init(RawBuffer_empty());
}

bool SyntaxText_isEmpty(SyntaxText_t self) {
    return RawBuffer_isEmpty(self.buffer);
}

bool SyntaxText_equals(SyntaxText_t lhs, SyntaxText_t rhs) {
    return RawBuffer_equals(lhs.buffer, rhs.buffer);
}
