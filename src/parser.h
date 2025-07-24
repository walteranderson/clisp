#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

#include "expr.h"
#include "tokenizer.h"

typedef struct {
    bool is_error;
    union {
        Expr expr;
        const char* error;
    };
} ParseResult;

ParseResult parse_expr(Token token);

void print_parse_result(ParseResult result);

#endif // PARSER_H
