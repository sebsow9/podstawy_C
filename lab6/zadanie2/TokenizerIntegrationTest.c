#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"

void simulate_input(const char *input) {
    FILE *fp = fopen("input.txt", "w");
    if (fp != NULL) {
        fputs(input, fp);
        fclose(fp);
    }
    freopen("input.txt", "r", stdin);
}

int main() {
    const char *input = "abc 123\ndef 456\n";
    simulate_input(input);

    int argc = 1;
    char *argv[] = {"integration_test"};

    int result = run_main_program(argc, argv);

    printf("Integration Test Result: %s\n", result == 0 ? "PASS" : "FAIL");

    return result;
}
