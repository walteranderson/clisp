#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "tokenizer.h"

#define REPL_BUFFER_MAX 256

void eval_input(const char* input)
{
    Token token = next_token(input);
    do {
        ParseResult result = parse_expr(token);
        print_parse_result(result);
        if (result.is_error == true) {
            return;
        }
        token = next_token(result.end);
    } while (true);
}

int main(void)
{
    char buffer[REPL_BUFFER_MAX];

    while (true) {
        printf("> ");
        if (fgets(buffer, REPL_BUFFER_MAX, stdin) == NULL) {
            return -1;
        }
        eval_input(buffer);
    }
    return 0;
}
