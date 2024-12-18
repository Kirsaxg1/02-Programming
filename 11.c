#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DELIMITERS " .,:;?!\n\t"
#define N 1024

int tokenize(const char* initial, int (*detector)(int), int accept_empty_lexems, char*** lexems, size_t* lexems_count);


int isDelimiter(int c) {
    const char* delims = DELIMITERS;
    for (int i = 0; delims[i] != '\0'; i++) {
        if (c == delims[i]) {
            return 0;  
        }
    }
    return 1;  
}


int tokenize(const char* initial, int (*detector)(int), int accept_empty_lexems, char*** lexems, size_t* lexems_count) {

    if (initial == NULL) return 1;
    if (detector == NULL) return 2;
    if (lexems == NULL) return 3;
    if (lexems_count == NULL) return 4;

    *lexems = NULL;
    *lexems_count = 0;

    size_t capacity = 10; 
    char** result = (char**)malloc(capacity * sizeof(char*));
    if (result == NULL) return 5;

    size_t current_size = 0;
    const char* start = initial;

    while (*start) {
        
        while (*start && !detector(*start)) start++;

        if (!*start) break; 

        const char* end = start;
        while (*end && detector(*end)) end++;


        size_t token_len = end - start;

        if (token_len > 0 || accept_empty_lexems) {
            char* token = (char*)malloc((token_len + 1) * sizeof(char));
            if (token == NULL) {
                for (size_t i = 0; i < current_size; i++) {
                    free(result[i]);
                }
                free(result);
                return 5;
            }

            strncpy(token, start, token_len);
            token[token_len] = '\0';

            if (current_size >= capacity) {
                capacity *= 2;
                char** temp = (char**)realloc(result, capacity * sizeof(char*));
                if (temp == NULL) {
                    for (size_t i = 0; i < current_size; i++) {
                        free(result[i]);
                    }
                    free(result);
                    free(token);
                    return 5;
                }
                result = temp;
            }
            result[current_size++] = token;
        }
        start = end;
    }

    *lexems = result;
    *lexems_count = current_size;

    return 0;
}


int main() {
    char initial[N];
    char** lexems = NULL;
    size_t lexems_count = 0;
    int status;

    printf("Enter str: ");
    if (fgets(initial, N, stdin) == NULL) {
        printf("error read str.\n");
        return 1;
    }

    status = tokenize(initial, isDelimiter, 0, &lexems, &lexems_count);

    if (status != 0) {
        printf("error: %d\n", status);
        return 1;
    }

    printf("Tokens:\n");
    for (size_t i = 0; i < lexems_count; i++) {
        puts(lexems[i]);
        free(lexems[i]);  
    }

    free(lexems); 

    return 0;
}