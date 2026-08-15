#pragma once

#include "hien/parse/tokenize/Lexeme.h"
#include "parse/TokenSpec.h"

typedef enum ExpressionStart_t {
    EXPRSTART_INTEGERLITERAL,

    MAX_EXPRSTART
} ExpressionStart_t;

ExpressionStart_t ExpressionStart_lookup(Lexeme_t lexeme);

TokenSpec_t ExpressionStart_spec(ExpressionStart_t self);
