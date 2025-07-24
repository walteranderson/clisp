#ifndef EXPR_H
#define EXPR_H

typedef struct Atom Atom;
typedef struct Cons Cons;

typedef enum {
    ATOM_SYMBOL,
    ATOM_STRING,
    ATOM_INT,
} AtomKind;

typedef enum {
    EXPR_ATOM,
    EXPR_CONS,
    EXPR_VOID,
} ExprKind;

typedef struct {
    ExprKind kind;
    union {
        Atom* atom;
        Cons* cons;
    };
} Expr;

typedef struct Atom {
    AtomKind kind;
    union {
        long int num;
        const char* str;
        const char* symbol;
    };
} Atom;

typedef struct Cons {
    Expr car;
    Expr cdr;
} Cons;

void print_atom(Atom* atom);

const char* expr_kind_to_string(ExprKind kind);
const char* atom_kind_to_string(AtomKind kind);

Atom* create_symbol_atom(const char* begin, const char* end);
Atom* create_string_atom(const char* begin, const char* end);
Atom* create_int_atom(long int x);

Cons* create_cons(Expr car, Expr cdr);

Expr create_atom_expr(Atom* atom);
Expr create_void_expr();
Expr create_cons_expr(Cons* cons);

#endif // EXPR_H
