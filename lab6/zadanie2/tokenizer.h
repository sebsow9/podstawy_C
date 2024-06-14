#ifndef TOKENIZER_H
#define TOKENIZER_H

typedef struct {
    int start;
    int end;
    char type[10];
} Token;

int is_number(const char *str, int base);
Token* extract_valid_tokens(char **lines, int num_lines, int base, int *token_count);
int run_main_program(int argc, char *argv[]);

#endif // TOKENIZER_H
