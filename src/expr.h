#ifndef EXPR_H
#define EXPR_H

typedef enum {
    ATOM_SYMBOL,
    ATOM_STRING,
    ATOM_INT,
} AtomKind;

typedef struct {
    AtomKind kind;
    union {
        long int num;
        const char* str;
        const char* symbol;
    };
} Atom;

typedef enum {
    EXPR_ATOM,
    EXPR_CONS,
    EXPR_VOID,
} ExprKind;

typedef struct {
    ExprKind kind;
    union {
        Atom* atom;
    };
} Expr;

void print_atom(Atom* atom);

const char* expr_kind_to_string(ExprKind kind);
const char* atom_kind_to_string(AtomKind kind);

Atom* create_symbol_atom(const char* begin, const char* end);
Atom* create_string_atom(const char* begin, const char* end);
Atom* create_int_atom(long int x);

Expr create_atom_expr(Atom* atom);

#endif // EXPR_H
