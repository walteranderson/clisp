#include "tokenizer.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

static Token new_token(const char* begin, const char* end)
{
    Token token = {
        .begin = begin,
        .end = end,
    };
    return token;
}

static const char* skip_whitespace(const char* str)
{
    assert(str);
    while (*str != 0 && isspace(*str)) {
        str++;
    }
    return str;
}

static bool is_symbol_char(char c)
{
    static const char symbols[] = {
        '(', ')', '.', ',', '\'', '"'
    };
    static const size_t symbol_length = sizeof(symbols) / sizeof(char);

    for (size_t i = 0; i < symbol_length; i++) {
        if (c == symbols[i] || isspace(c)) {
            return false;
        }
    }
    return true;
}

static const char* next_non_symbol(const char* str)
{
    assert(str);
    while (*str != 0 && !is_symbol_char(*str)) {
        str++;
    }
    return str;
}

static const char* next_quote(const char* str)
{
    assert(str);
    while (*str != 0 && *str != '"') {
        str++;
    }
    return str;
}

Token next_token(const char* str)
{
    assert(str);

    str = skip_whitespace(str);
    if (*str == 0) {
        return new_token(str, str);
    }

    switch (*str) {
    case '(':
    case ')':
    case '.':
    case ',':
    case '\'':
        return new_token(str, str + 1);
    case '"': {
        const char* str_end = next_quote(str + 1);
        return new_token(str, str_end == 0 ? str_end : str_end + 1);
    } break;
    default: {
        const char* str_end = next_non_symbol(str + 1);
        return new_token(str, str_end);
    } break;
    }
}
