#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "expr.h"

void print_atom(Atom* atom)
{
    printf("Atom:\n");
    printf("  kind=%s\n", atom_kind_to_string(atom->kind));
    switch (atom->kind) {
    case ATOM_SYMBOL: {
        printf("  value=%s\n", atom->symbol);
    } break;
    case ATOM_STRING: {
        printf("  value=%s\n", atom->str);
    } break;
    case ATOM_INT: {
        printf("  value=%ld\n", atom->num);
    } break;
    }
}

const char* expr_kind_to_string(ExprKind kind)
{
    switch (kind) {
    case EXPR_ATOM:
        return "EXPR_ATOM";
    case EXPR_CONS:
        return "EXPR_CONS";
    case EXPR_VOID:
        return "EXPR_VOID";
    default:
        return "UNKNOWN EXPR";
    }
}

const char* atom_kind_to_string(AtomKind kind)
{
    switch (kind) {
    case ATOM_SYMBOL:
        return "ATOM_SYMBOl";
    case ATOM_STRING:
        return "ATOM_STRING";
    case ATOM_INT:
        return "ATOM_INT";
    default:
        return "UNKNOWN ATOM";
    }
}

Atom* create_symbol_atom(const char* begin, const char* end)
{
    Atom* atom = malloc(sizeof(Atom));
    if (atom == NULL) {
        return NULL;
    }

    size_t length = end == NULL ? strlen(begin) : end - begin;
    char* str = (char*)malloc(length + 1);
    if (str == NULL) {
        free(atom);
        return NULL;
    }
    str[length] = '\0';
    strncpy(str, begin, length);

    atom->kind = ATOM_SYMBOL;
    atom->symbol = str;
    return atom;
}

Atom* create_int_atom(long int x)
{
    Atom* atom = malloc(sizeof(Atom));
    if (atom == NULL) {
        return NULL;
    }

    atom->kind = ATOM_INT;
    atom->num = x;
    return atom;
}

Atom* create_string_atom(const char* begin, const char* end)
{
    Atom* atom = malloc(sizeof(Atom));
    if (atom == NULL) {
        return NULL;
    }

    size_t length = end - begin;
    char* str = (char*)malloc(length + 1);
    if (str == NULL) {
        free(atom);
        return NULL;
    }
    str[length] = '\0';
    strncpy(str, begin, length);

    atom->kind = ATOM_STRING;
    atom->symbol = str;
    return atom;
}

Expr create_atom_expr(Atom* atom)
{
    Expr expr = {
        .kind = EXPR_ATOM,
        .atom = atom,
    };
    return expr;
}
