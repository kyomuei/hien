#pragma once

typedef struct Range_t {
    int lowerBound;
    int upperBound;
} Range_t;

Range_t Range_init(int lowerBound, int upperBound);

#ifndef FOR_IN_RANGE
#define FOR_IN_RANGE(var, range) for (int var = range.lowerBound; var < range.upperBound; var++)
#endif
