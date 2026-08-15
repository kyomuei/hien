#pragma once

#include "hien/syntax/SyntaxNode.h"
#include "parse/Parser.h"

SyntaxNode_t * Parser_parseSourceFile(Parser_t *self);

SyntaxNode_t * Parser_parseStatement(Parser_t *self);

SyntaxNode_t * Parser_parseReturnStatement(Parser_t *self);

SyntaxNode_t * Parser_parseExpression(Parser_t *self);

SyntaxNode_t * Parser_parseNumberExpression(Parser_t *self);

bool Parser_isAtStartOfExpression(Parser_t const *self);
