#include "hien/syntax/SyntaxNode.h"
#include "hien/syntax/SyntaxText.h"
#include <stdlib.h>

SyntaxNode_t * SyntaxNode_node(SyntaxKind_t kind, int childrenCount, SyntaxNode_t **children) {
    SyntaxNode_t *node = calloc(1, sizeof(SyntaxNode_t));
    *node = (SyntaxNode_t) {
        .kind = kind,
        .childrenCount = childrenCount,
        .children = children,
        .text = SyntaxText_empty(),
    };
    return node;
}

SyntaxNode_t * SyntaxNode_leaf(SyntaxKind_t kind, SyntaxText_t text) {
    SyntaxNode_t *leaf = calloc(1, sizeof(SyntaxNode_t));
    *leaf = (SyntaxNode_t) {
        .kind = kind,
        .childrenCount = 0,
        .children = NULL,
        .text = text,
    };
    return leaf;
}
