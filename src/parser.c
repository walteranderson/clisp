#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "expr.h"
#include "parser.h"
#include "tokenizer.h"

void print_parse_result(ParseResult result)
{
    if (result.is_error == true) {
        printf("ERROR: %s\n", result.error);
        return;
    }

    switch (result.expr.kind) {
    case EXPR_ATOM: {
        print_atom(result.expr.atom);
    } break;
    case EXPR_CONS: {
        printf("expr_cons: TODO\n");
    } break;
    case EXPR_VOID: {
        printf("void\n");
    } break;
    }
}

static ParseResult parse_error(const char* msg)
{
    ParseResult result = {
        .is_error = true,
        .error = msg,
    };
    return result;
}

static ParseResult parse_success(Expr expr)
{
    ParseResult result = {
        .is_error = false,
        .expr = expr,
    };
    return result;
}

ParseResult parse_symbol(Token token)
{
    Atom* atom = create_symbol_atom(token.begin, token.end);
    return parse_success(create_atom_expr(atom));
}

ParseResult parse_int(Token token)
{
    char* endptr = 0;
    long int x = strtol(token.begin, &endptr, 10);
    Atom* atom = create_int_atom(x);
    return parse_success(create_atom_expr(atom));
}

ParseResult parse_string(Token token)
{
    if (*(token.end - 1) != '"') {
        return parse_error("Missing closing quote");
    }

    Atom* atom = create_string_atom(token.begin + 1, token.end - 1);
    return parse_success(create_atom_expr(atom));
}

ParseResult parse_list(Token token)
{
    (void)token;
    return parse_error("TODO: parse_list not implemented");
}

ParseResult parse_expr(Token token)
{
    if (*token.begin == 0) {
        return parse_error("EOF");
    }

    switch (*token.begin) {
    case '"':
        return parse_string(token);
    case '(':
        return parse_list(token);
    }

    if (isdigit(*token.begin)) {
        return parse_int(token);
    }

    return parse_symbol(token);
}
