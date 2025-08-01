#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "expr.h"
#include "parser.h"
#include "tokenizer.h"

void print_expr(Expr expr)
{
    switch (expr.kind) {
    case EXPR_ATOM: {
        print_atom(expr.atom);
    } break;
    case EXPR_CONS: {
        print_expr(expr.cons->car);
        print_expr(expr.cons->cdr);
    } break;
    case EXPR_VOID: {
        printf("void\n");
    } break;
    }
}

void print_parse_result(ParseResult result)
{
    if (result.is_error == true) {
        printf("ERROR: %s\n", result.error);
        return;
    }
    print_expr(result.expr);
}

static ParseResult parse_error(const char* msg, const char* end)
{
    ParseResult result = {
        .is_error = true,
        .end = end,
        .error = msg,
    };
    return result;
}

static ParseResult parse_success(Expr expr, const char* end)
{
    ParseResult result = {
        .is_error = false,
        .end = end,
        .expr = expr,
    };
    return result;
}

ParseResult parse_symbol(Token token)
{
    Atom* atom = create_symbol_atom(token.begin, token.end);
    return parse_success(create_atom_expr(atom), token.end);
}

ParseResult parse_int(Token token)
{
    char* endptr = 0;
    long int x = strtol(token.begin, &endptr, 10);
    Atom* atom = create_int_atom(x);
    return parse_success(create_atom_expr(atom), token.end);
}

ParseResult parse_string(Token token)
{
    if (*(token.end - 1) != '"') {
        return parse_error("Missing closing quote", token.end);
    }

    Atom* atom = create_string_atom(token.begin + 1, token.end - 1);
    return parse_success(create_atom_expr(atom), token.end);
}

ParseResult parse_cdr(Token token)
{
    if (*token.begin != '.') {
        return parse_error("Expected .", token.end);
    }

    token = next_token(token.end);
    ParseResult cdr = parse_expr(token);
    if (cdr.is_error == true) {
        return cdr;
    }

    token = next_token(token.end);
    printf("tok: %c\n", *token.begin);
    if (*token.begin != ')') {
        return parse_error("Expected )", token.end);
    }

    return parse_success(cdr.expr, token.end);
}

ParseResult parse_list(Token token)
{
    if (*token.begin != '(') {
        return parse_error("Expected (", token.end);
    }

    token = next_token(token.end);
    if (*token.begin == ')') {
        return parse_success(
            create_atom_expr(create_symbol_atom("nil", NULL)),
            token.end);
    }

    ParseResult car = parse_expr(token);
    if (car.is_error == true) {
        return car;
    }

    Cons* list = create_cons(car.expr, create_void_expr());
    Cons* cons = list;
    token = next_token(car.end);
    while (*token.begin != 0 && *token.begin != '.' && *token.begin != ')') {
        car = parse_expr(token);
        if (car.is_error) {
            return car;
        }
        cons->cdr = create_cons_expr(create_cons(car.expr, create_void_expr()));
        cons = cons->cdr.cons;
        token = next_token(car.end);
    }

    ParseResult cdr = *token.begin == '.'
        ? parse_cdr(token)
        : parse_success(create_atom_expr(create_symbol_atom("nil", NULL)), token.end);
    if (cdr.is_error) {
        return cdr;
    }

    cons->cdr = cdr.expr;

    return parse_success(create_cons_expr(list), cdr.end);
}

ParseResult parse_expr(Token token)
{
    if (*token.begin == 0) {
        return parse_error("EOF", 0);
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
