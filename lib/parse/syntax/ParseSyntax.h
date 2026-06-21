#pragma once

#include "hien/syntax/SyntaxNode.h"
#include "parse/Parser.h"

SyntaxNode_t * Parser_parseSourceFile(Parser_t *self);

SyntaxNode_t * Parser_parseNumber(Parser_t *self);
