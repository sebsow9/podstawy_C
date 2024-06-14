#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenizer.h"

int is_number(const char *str, int base) {
    char *end;
    strtol(str, &end, base);
    return *end == '\0';
}

Token* extract_valid_tokens(char **lines, int num_lines, int base, int *token_count) {
    int token_size = 10;
    int index = 0;
    *token_count = 0;

    Token *tokens = malloc(token_size * sizeof(Token));
    if (tokens == NULL) {
        perror("Failed to allocate memory for tokens");
        return NULL;
    }

    for (int i = 0; i < num_lines; i++) {
        char *line = lines[i];
        int start = 0;
        int in_word = 0;
        int in_number = 0;

        for (int j = 0; line[j] != '\0'; j++) {
            if (isdigit(line[j]) || (base == 16 && ((line[j] >= 'A' && line[j] <= 'F') || (line[j] >= 'a' && line[j] <= 'f')))) {
                if (!in_number) {
                    if (in_word && j - start > 2) {
                        if (index >= token_size) {
                            token_size *= 2;
                            tokens = realloc(tokens, token_size * sizeof(Token));
                            if (tokens == NULL) {
                                perror("Failed to reallocate memory for tokens");
                                return NULL;
                            }
                        }
                        tokens[index].start = start;
                        tokens[index].end = j - 1;
                        strcpy(tokens[index].type, "word");
                        index++;
                        in_word = 0;
                    }
                    in_number = 1;
                    start = j;
                }
            } else if (isalpha(line[j])) {
                if (!in_word) {
                    if (in_number) {
                        char saved = line[j];
                        line[j] = '\0';
                        if (is_number(line + start, base)) {
                            if (index >= token_size) {
                                token_size *= 2;
                                tokens = realloc(tokens, token_size * sizeof(Token));
                                if (tokens == NULL) {
                                    perror("Failed to reallocate memory for tokens");
                                    return NULL;
                                }
                            }
                            tokens[index].start = start;
                            tokens[index].end = j - 1;
                            strcpy(tokens[index].type, "number");
                            index++;
                        }
                        line[j] = saved;
                        in_number = 0;
                    }
                    in_word = 1;
                    start = j;
                }
            } else {
                if (in_number) {
                    char saved = line[j];
                    line[j] = '\0';
                    if (is_number(line + start, base)) {
                        if (index >= token_size) {
                            token_size *= 2;
                            tokens = realloc(tokens, token_size * sizeof(Token));
                            if (tokens == NULL) {
                                perror("Failed to reallocate memory for tokens");
                                return NULL;
                            }
                        }
                        tokens[index].start = start;
                        tokens[index].end = j - 1;
                        strcpy(tokens[index].type, "number");
                        index++;
                    }
                    line[j] = saved;
                    in_number = 0;
                }
                if (in_word && j - start > 2) {
                    if (index >= token_size) {
                        token_size *= 2;
                        tokens = realloc(tokens, token_size * sizeof(Token));
                        if (tokens == NULL) {
                            perror("Failed to reallocate memory for tokens");
                            return NULL;
                        }
                    }
                    tokens[index].start = start;
                    tokens[index].end = j - 1;
                    strcpy(tokens[index].type, "word");
                    index++;
                    in_word = 0;
                }
                in_number = 0;
                in_word = 0;
            }
        }

        if (in_number && is_number(line + start, base)) {
            if (index >= token_size) {
                token_size *= 2;
                tokens = realloc(tokens, token_size * sizeof(Token));
                if (tokens == NULL) {
                    perror("Failed to reallocate memory for tokens");
                    return NULL;
                }
            }
            tokens[index].start = start;
            tokens[index].end = strlen(line) - 1;
            strcpy(tokens[index].type, "number");
            index++;
        }

        if (in_word && strlen(line + start) > 2) {
            if (index >= token_size) {
                token_size *= 2;
                tokens = realloc(tokens, token_size * sizeof(Token));
                if (tokens == NULL) {
                    perror("Failed to reallocate memory for tokens");
                    return NULL;
                }
            }
            tokens[index].start = start;
            tokens[index].end = strlen(line) - 1;
            strcpy(tokens[index].type, "word");
            index++;
        }
    }
    *token_count = index;
    return tokens;
}

int run_main_program(int argc, char *argv[]) {
    int base = 10;

    if (argc > 1) {
        base = atoi(argv[1]);
        if (base < 2 || base > 16) {
            fprintf(stderr, "Invalid base. Please provide a base between 2 and 16.\n");
            return 1;
        }
    }

    int initial_size = 3;
    char **lines = malloc(initial_size * sizeof(char*));
    if (lines == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    char buffer[1024];
    int count = 0;

    printf("Enter lines of text (CTRL+D to stop):\n");

    while (fgets(buffer, sizeof(buffer), stdin)) {
        if (count >= initial_size) {
            int new_size = initial_size * 2;
            char **new_lines = realloc(lines, new_size * sizeof(char*));
            if (new_lines == NULL) {
                perror("Failed to reallocate memory");
                break;
            }
            lines = new_lines;
            initial_size = new_size;
        }

        lines[count] = malloc(strlen(buffer) + 1);
        if (lines[count] == NULL) {
            perror("Failed to allocate memory for line");
            break;
        }
        strcpy(lines[count], buffer);
        count++;
    }

    if (count == 0) {
        fprintf(stderr, "No lines entered.\n");
        free(lines);
        return 1;
    }

    int token_count;
    Token *tokens = extract_valid_tokens(lines, count, base, &token_count);

    for (int i = 0; i < token_count; i++) {
        printf("Token type: %s, start: %d, end: %d\n", tokens[i].type, tokens[i].start, tokens[i].end);
    }

    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
    free(tokens);

    return 0;
}
