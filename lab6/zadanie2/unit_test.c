#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tokenizer.h"

void test_is_number() {
    assert(is_number("123", 10) == 1);
    assert(is_number("abc", 10) == 0);
    assert(is_number("1A", 16) == 1);
    assert(is_number("1G", 16) == 0);
    assert(is_number("101", 2) == 1);
    assert(is_number("102", 2) == 0);

    printf("All tests for is_number passed!\n");
}

void test_extract_valid_tokens() {
    char *lines[] = {"abc 123 def", "456 ghi 789"};
    int token_count;
    printf("Calling extract_valid_tokens\n");
    Token *tokens = extract_valid_tokens(lines, 2, 10, &token_count);

    assert(tokens != NULL);  
    assert(token_count == 4);
    if (tokens != NULL) {
        printf("Token count: %d\n", token_count);

        for (int i = 0; i < token_count; i++) {
            printf("Token %d: type=%s, start=%d, end=%d\n", i, tokens[i].type, tokens[i].start, tokens[i].end);
        }

        assert(strcmp(tokens[0].type, "word") == 0);
        assert(tokens[0].start == 0 && tokens[0].end == 2);

        assert(strcmp(tokens[1].type, "number") == 0);
        assert(tokens[1].start == 4 && tokens[1].end == 6);

        assert(strcmp(tokens[2].type, "word") == 0);
        assert(tokens[2].start == 8 && tokens[2].end == 10);

        assert(strcmp(tokens[3].type, "number") == 0);
        assert(tokens[3].start == 0 && tokens[3].end == 2);

        free(tokens);
    }

    printf("All tests for extract_valid_tokens passed!\n");
}

int main() {
    test_is_number();
    test_extract_valid_tokens();
    return 0;
}
