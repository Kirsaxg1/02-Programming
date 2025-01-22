#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef enum {
    STATUS_SUCCESS,
    STATUS_MEMORY_ERROR,
    STATUS_INVALID_INPUT,
    STATUS_INVALID_FLAG
} Status;

Status string_length(const char* str, size_t* result) {
    if (str == NULL || result == NULL) {
        return STATUS_INVALID_INPUT;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    *result = len;
    return STATUS_SUCCESS;
}

Status string_reverse(const char* str, char** result) {
    if (str == NULL || result == NULL) {
        return STATUS_INVALID_INPUT;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    *result = (char*)malloc(sizeof(char) * (len + 1));
    if (*result == NULL) {
        return STATUS_MEMORY_ERROR;
    }
    size_t i; 
    for (i = 0; i < len; i++) {
        (*result)[i] = str[len - 1 - i];
    }
    (*result)[len] = '\0';
    return STATUS_SUCCESS;
}

Status string_toupper_odd(const char* str, char** result) {
    if (str == NULL || result == NULL) {
        return STATUS_INVALID_INPUT;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    *result = (char*)malloc(sizeof(char) * (len + 1));
    if (*result == NULL) {
        return STATUS_MEMORY_ERROR;
    }
    size_t i;
    for (i = 0; i < len; i++) {
        (*result)[i] = (i % 2 != 0) ? toupper((int)str[i]) : str[i];
    }
    (*result)[len] = '\0';
    return STATUS_SUCCESS;
}

Status string_sort(const char* str, char** result) {
    if (str == NULL || result == NULL) {
        return STATUS_INVALID_INPUT;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* digits = (char*)malloc(sizeof(char) * (len + 1));
    char* letters = (char*)malloc(sizeof(char) * (len + 1));
    char* others = (char*)malloc(sizeof(char) * (len + 1));
    if (digits == NULL || letters == NULL || others == NULL) {
        free(digits);
        free(letters);
        free(others);
        return STATUS_MEMORY_ERROR;
    }
    size_t i;
    size_t digit_count = 0, letter_count = 0, other_count = 0;
    for (i = 0; i < len; i++) {
        if (isdigit((int)str[i])) {
            digits[digit_count++] = str[i];
        }
        else if (isalpha((int)str[i])) {
            letters[letter_count++] = str[i];
        }
        else {
            others[other_count++] = str[i];
        }
    }
    digits[digit_count] = '\0';
    letters[letter_count] = '\0';
    others[other_count] = '\0';

    size_t total_len = digit_count + letter_count + other_count;
    *result = (char*)malloc(sizeof(char) * (total_len + 1));
    if (*result == NULL) {
        free(digits);
        free(letters);
        free(others);
        return STATUS_MEMORY_ERROR;
    }

    size_t k = 0;
    for (i = 0; i < digit_count; i++) {
        (*result)[k++] = digits[i];
    }
    for (i = 0; i < letter_count; i++) {
        (*result)[k++] = letters[i];
    }
    for (i = 0; i < other_count; i++) {
        (*result)[k++] = others[i];
    }
    (*result)[total_len] = '\0';

    free(digits);
    free(letters);
    free(others);
    return STATUS_SUCCESS;
}

Status string_concat_random(int argc, char* argv[], char** result) {
    if (argc < 4 || argv == NULL || result == NULL) {
        return STATUS_INVALID_INPUT;
    }

    unsigned int seed = (unsigned int)atoi(argv[3]);
    srand(seed);

    size_t total_len = 0;
    int i;
    for (i = 4; i < argc; i++) {
        if ((i - 3) % 2 != 0) {
            size_t len = 0;
            while (argv[i][len] != '\0') {
                len++;
            }
            total_len += len;
        }
    }

    *result = (char*)malloc(sizeof(char) * (total_len + 1));
    if (*result == NULL) {
        return STATUS_MEMORY_ERROR;
    }

    int* indices = (int*)malloc(sizeof(int) * (argc - 4));
    if (indices == NULL) {
        free(*result);
        return STATUS_MEMORY_ERROR;
    }

    for (i = 0; i < argc - 4; i++) {
        indices[i] = i + 4;
    }

    for (i = 0; i < argc - 4; i++) {
        int j = i + rand() % (argc - 4 - i);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    size_t k = 0;
    int j;
    for (i = 0; i < argc - 4; i++) {
        if ((indices[i] - 3) % 2 != 0) {
            const char* str = argv[indices[i]];
            for (j = 0; str[j] != '\0'; j++) {
                (*result)[k++] = str[j];
            }
        }
    }
    (*result)[total_len] = '\0';

    free(indices);
    return STATUS_SUCCESS;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-l|-r|-u|-n|-c] string [seed [strings...]]\n", argv[0]);
        return 1;
    }

    char* result = NULL;
    Status status = STATUS_SUCCESS;

    if (argv[1][0] == '-' && argv[1][1] == 'l') {
        size_t len;
        status = string_length(argv[2], &len);
        if (status == STATUS_SUCCESS) {
            printf("Length: %zu\n", len);
        }
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'r') {
        status = string_reverse(argv[2], &result);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'u') {
        status = string_toupper_odd(argv[2], &result);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'n') {
        status = string_sort(argv[2], &result);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'c') {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s -c seed string1 string2 ...\n", argv[0]);
            return 1;
        }
        status = string_concat_random(argc, argv, &result);
    }
    else {
        fprintf(stderr, "Invalid flag\n");
        return 1;
    }

    if (status == STATUS_MEMORY_ERROR) {
        fprintf(stderr, "Error: Memory allocation failed\n");
    }
    else if (status == STATUS_INVALID_INPUT) {
        fprintf(stderr, "Error: Invalid input\n");
    }
    else if (result != NULL) {
        printf("Result: %s\n", result);
        free(result);
    }

    return 0;
}