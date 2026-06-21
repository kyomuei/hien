#include "parse/syntax/ParseSyntax.h"

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/parse/Parser.h"
#include "hien/syntax/SyntaxNode.h"
#include "hien/syntax/TokenKind.h"
#include "parse/Parser.h"
#include <stdlib.h>

SyntaxNode_t * Parser_parse(SyntaxText_t source) {
    Parser_t parser = Parser_init(source.buffer);
    return Parser_parseSourceFile(&parser);
}

SyntaxNode_t * Parser_parseSourceFile(Parser_t *self) {
    SyntaxNode_t *number =  Parser_parseNumber(self);
    SyntaxNode_t *node = calloc(1, sizeof(SyntaxNode_t));
    SyntaxNode_t **children = calloc(1, sizeof(SyntaxNode_t *));
    children[0] = number;
    *node = (SyntaxNode_t) {
        .kind = SYNTAXKIND_SOURCEFILE,
        .children = children,
        .childrenCount = 1,
    };
    
    if (!Parser_consumeIf(self, TOKENKIND_END_OF_FILE)) {
        exit(1);
    }

    return node;
}

SyntaxNode_t *Parser_parseNumber(Parser_t *self) {
    Lexeme_t token = self->currentToken;
    if (Parser_consumeIf(self, TOKENKIND_INTEGER_LITERAL)) {
        SyntaxNode_t *node = calloc(1, sizeof(SyntaxNode_t));
        *node = (SyntaxNode_t) {
            .kind = SYNTAXKIND_NUMBER,
            .text = SyntaxText_fromPointer(token.start, token.textLength),
        };
        return node;
    }

    exit(1);
}
