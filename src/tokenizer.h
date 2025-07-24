#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct {
    const char* begin;
    const char* end;
} Token;

Token next_token(const char* str);

#endif // TOKENIZER_H
