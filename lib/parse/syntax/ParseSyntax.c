#include "parse/syntax/ParseSyntax.h"

#include "hien/parse/tokenize/Lexeme.h"
#include "hien/parse/Parser.h"
#include "hien/syntax/Keyword.h"
#include "hien/syntax/SyntaxKind.h"
#include "hien/syntax/SyntaxNode.h"
#include "hien/syntax/TokenKind.h"
#include "parse/Parser.h"
#include "parse/TokenSpec.h"
#include <stdlib.h>

SyntaxNode_t * Parser_parse(SyntaxText_t source) {
    Parser_t parser = Parser_init(source.buffer);
    return Parser_parseSourceFile(&parser);
}

SyntaxNode_t * Parser_parseSourceFile(Parser_t *self) {
    if (Parser_isAt(self, TokenSpec_token(TOKENKIND_END_OF_FILE))) {
        SyntaxNode_t *node = calloc(1, sizeof(SyntaxNode_t));
        *node = (SyntaxNode_t) {
            .kind = SYNTAXKIND_SOURCEFILE,
            .childrenCount = 0,
            .children = NULL,
        };

        return node;
    }

    SyntaxNode_t *node = calloc(1, sizeof(SyntaxNode_t));
    SyntaxNode_t **children = calloc(1, sizeof(SyntaxNode_t *));
    children[0] = Parser_parseStatement(self);
    *node = (SyntaxNode_t) {
        .kind = SYNTAXKIND_SOURCEFILE,
        .children = children,
        .childrenCount = 1,
    };
    
    if (!Parser_consumeIf(self, TokenSpec_token(TOKENKIND_END_OF_FILE))) {
        exit(1);
    }

    return node;
}

SyntaxNode_t * Parser_parseStatement(Parser_t *self) {
    return Parser_parseReturnStatement(self);
}

SyntaxNode_t * Parser_parseReturnStatement(Parser_t *self) {
    Parser_eat(self, TokenSpec_keyword(KEYWORD_RETURN));

    SyntaxNode_t **children = NULL;
    int childrenCount = 0;

    if (Parser_isAt(self, TokenSpec_token(TOKENKIND_INTEGER_LITERAL))) {
        children = calloc(1, sizeof(SyntaxNode_t *));
        children[0] = Parser_parseNumber(self);
        childrenCount = 1;
    }

    SyntaxNode_t *node = calloc(1, sizeof(SyntaxNode_t));
    *node = (SyntaxNode_t) {
        .kind = SYNTAXKIND_STMT_RETURN,
        .children = children,
        .childrenCount = childrenCount,
    };
    return node;
}

SyntaxNode_t *Parser_parseNumber(Parser_t *self) {
    Lexeme_t token = self->currentToken;
    if (Parser_consumeIf(self, TokenSpec_token(TOKENKIND_INTEGER_LITERAL))) {
        SyntaxNode_t *node = calloc(1, sizeof(SyntaxNode_t));
        *node = (SyntaxNode_t) {
            .kind = SYNTAXKIND_NUMBER,
            .text = Lexeme_tokenText(token),
        };
        return node;
    }

    exit(1);
}
