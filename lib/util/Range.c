#include "hien/util/Range.h"

#include <assert.h>

Range_t Range_init(int lowerBound, int upperBound) {
    assert(lowerBound <= upperBound);
    return (Range_t) { .lowerBound = lowerBound, .upperBound = upperBound };
}
