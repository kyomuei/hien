#include "hien/syntax/SyntaxText.h"

#include "hien/syntax/SourceBuffer.h"
#include <stdbool.h>
#include <string.h>

SyntaxText_t SyntaxText_init(SourceBuffer_t buffer) {
    return (SyntaxText_t) { .buffer = buffer };
}

SyntaxText_t SyntaxText_fromLiteral(char const *literal) {
    return SyntaxText_fromPointer(literal, strlen(literal));
}

SyntaxText_t SyntaxText_fromPointer(char const *baseAddress, int count) {
    return SyntaxText_init(SourceBuffer_init(baseAddress, count));
}

char const * SyntaxText_baseAddress(SyntaxText_t self) {
    return SourceBuffer_baseAddress(self.buffer);
}

int SyntaxText_count(SyntaxText_t self) {
    return SourceBuffer_count(self.buffer);
}

SyntaxText_t SyntaxText_empty() {
    return SyntaxText_init(SourceBuffer_empty());
}

bool SyntaxText_isEmpty(SyntaxText_t self) {
    return SourceBuffer_isEmpty(self.buffer);
}

bool SyntaxText_equals(SyntaxText_t lhs, SyntaxText_t rhs) {
    return SourceBuffer_equals(lhs.buffer, rhs.buffer);
}
