#pragma once

#include "hien/syntax/SyntaxKind.h"
#include "hien/syntax/SyntaxText.h"

typedef struct SyntaxNode_t SyntaxNode_t;

struct SyntaxNode_t {
    SyntaxKind_t kind;
    int childrenCount;
    SyntaxNode_t **children;
    SyntaxText_t text;
};
