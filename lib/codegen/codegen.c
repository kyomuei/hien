#include "hien/codegen/codegen.h"

#include "hien/syntax/SyntaxKind.h"
#include "hien/syntax/SyntaxNode.h"
#include "hien/syntax/SyntaxText.h"
#include <stdlib.h>
#include <stdio.h>

void codegen(SyntaxNode_t *node, FILE *output) {

    switch (node->kind) {
    case SYNTAXKIND_SOURCEFILE:
        fprintf(output, ".global _main\n");
        fprintf(output, "_main:\n");
        if (node->childrenCount == 0) {
            fprintf(output, "  mov w0, #0\n");
        } else {
            for (int i = 0; i < node->childrenCount; i++) {
                codegen(node->children[0], output);
            }
        }
        fprintf(output, "  ret\n");
        break;
    case SYNTAXKIND_NUMBER:
        fprintf(output, "  mov w0, #%*s\n", SyntaxText_count(node->text), SyntaxText_baseAddress(node->text));
        break;
    default:
        exit(1);
    }
}
