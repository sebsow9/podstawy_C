#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struktura do przechowywania informacji o tokenach
typedef struct {
    int start;   
    int end;     
    char type[10]; // Typ tokena: "number" lub "word"
} Token;

// Funkcja sprawdzająca, czy ciąg znaków jest liczbą w danym systemie liczbowym
int is_number(const char *str, int base) {
    char *end;
    strtol(str, &end, base);
    return *end == '\0';
}

// Funkcja wyodrębniająca liczby i wyrazy z linii tekstu
Token* extract_valid_tokens(char **lines, int num_lines, int base, int *token_count) {
    int token_size = 10; // Początkowy rozmiar tablicy tokenów
    int index = 0; // Aktualny indeks w tablicy tokenów
    *token_count = 0;

    // Alokacja pamięci dla tablicy tokenów
    Token *tokens = malloc(token_size * sizeof(Token));
    if (tokens == NULL) {
        perror("Failed to allocate memory for tokens");
        return NULL;
    }

    // Iteracja przez każdą linię tekstu
    for (int i = 0; i < num_lines; i++) {
        char *line = lines[i];
        int start = 0;
        int in_word = 0; // Flaga oznaczająca, czy jesteśmy wewnątrz wyrazu
        int in_number = 0; // Flaga oznaczająca, czy jesteśmy wewnątrz liczby

        // Iteracja przez każdy znak w linii
        for (int j = 0; line[j] != '\0'; j++) {
            // Sprawdzanie, czy znak jest cyfrą
            if (isdigit(line[j]) || (base == 16 && ((line[j] >= 'A' && line[j] <= 'F') || (line[j] >= 'a' && line[j] <= 'f')))) {
                if (!in_number) {
                    if (in_word && j - start > 2) {
                        // Zakończ poprzedni wyraz
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
                    in_number = 1; // Ustawienie flagi, że jesteśmy wewnątrz liczby
                    start = j; // Zapisanie indeksu początkowego liczby
                }
            } else if (isalpha(line[j])) { // Sprawdzanie, czy znak jest literą
                if (!in_word) {
                    if (in_number) {
                        // Zakończ poprzednią liczbę
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
                    in_word = 1; // Ustawienie flagi, że jesteśmy wewnątrz wyrazu
                    start = j; // Zapisanie indeksu początkowego wyrazu
                }
            } else { // Jeśli znak nie jest ani literą, ani cyfrą
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

        // Sprawdzanie, czy na końcu linii jest niesprawdzona liczba
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

        // Sprawdzanie, czy na końcu linii jest niesprawdzony wyraz
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
    *token_count = index; // Ustawienie liczby tokenów
    return tokens;
}

int main(int argc, char *argv[]) {
    int base = 10; // Domyślna podstawa systemu liczbowego

    if (argc > 1) {
        base = atoi(argv[1]); // Pobieranie podstawy systemu liczbowego z argumentów linii poleceń
        if (base < 2 || base > 16) {
            fprintf(stderr, "Invalid base. Please provide a base between 2 and 16.\n");
            return 1;
        }
    }

    int initial_size = 3; // Zaczynamy z tablicą o rozmiarze 3
    char **lines = malloc(initial_size * sizeof(char*));
    if (lines == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }

    char buffer[1024]; // Buffer do trzymania linijki
    int count = 0;

    printf("Enter lines of text (CTRL+D to stop):\n");

    // Czytamy linijki aż do EOF
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

    // Wypisywanie wyników
    for (int i = 0; i < token_count; i++) {
        printf("Token type: %s, start: %d, end: %d\n", tokens[i].type, tokens[i].start, tokens[i].end);
    }

    // Zwolnienie pamięci
    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);
    free(tokens);

    return 0;
}
