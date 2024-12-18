#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Функция для подсчета длины строки
char* string_length(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* result = (char*)malloc(sizeof(char) * (12 + 1)); // 12 достаточно для большинства чисел
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    sprintf(result, "%u", len);
    return result;
}

// Функция для обращения строки
char* string_reverse(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* result = (char*)malloc(sizeof(char) * (len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (unsigned int i = 0; i < len; i++) {
        result[i] = str[len - 1 - i];
    }
    result[len] = '\0';
    return result;
}

// Функция для преобразования символов на нечетных позициях в верхний регистр
char* string_toupper_odd(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* result = (char*)malloc(sizeof(char) * (len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (unsigned int i = 0; i < len; i++) {
        result[i] = (i % 2 != 0) ? toupper(str[i]) : str[i];
    }
    result[len] = '\0';
    return result;
}

// Функция для сортировки символов строки
char* string_sort(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* digits = (char*)malloc(sizeof(char) * (len + 1));
    char* letters = (char*)malloc(sizeof(char) * (len + 1));
    char* others = (char*)malloc(sizeof(char) * (len + 1));
    unsigned int digit_count = 0;
    unsigned int letter_count = 0;
    unsigned int other_count = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            digits[digit_count++] = str[i];
        }
        else if (isalpha(str[i])) {
            letters[letter_count++] = str[i];
        }
        else {
            others[other_count++] = str[i];
        }
    }
    digits[digit_count] = '\0';
    letters[letter_count] = '\0';
    others[other_count] = '\0';

    unsigned int total_len = digit_count + letter_count + other_count;
    char* result = (char*)malloc(sizeof(char) * (total_len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    unsigned int k = 0;
    for (unsigned int i = 0; i < digit_count; i++, k++) {
        result[k] = digits[i];
    }
    for (unsigned int i = 0; i < letter_count; i++, k++) {
        result[k] = letters[i];
    }
    for (unsigned int i = 0; i < other_count; i++, k++) {
        result[k] = others[i];
    }
    result[total_len] = '\0';

    free(digits);
    free(letters);
    free(others);
    return result;
}

// Функция для конкатенации строк в псевдослучайном порядке
char* string_concat_random(int argc, char* argv[]) {
    unsigned int seed = (unsigned int)atoi(argv[3]);
    srand(seed);

    unsigned int total_len = 0;
    for (int i = 4; i < argc; i++) {
        if ((i - 3) % 2 != 0) {
            unsigned int len = 0;
            while (argv[i][len] != '\0') {
                len++;
            }
            total_len += len;
        }
    }

    char* result = (char*)malloc(sizeof(char) * (total_len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    unsigned int k = 0;
    int* indices = (int*)malloc(sizeof(int) * (argc - 4));
    for (int i = 0; i < argc - 4; ++i) {
        indices[i] = i + 4;
    }

    for (int i = 0; i < argc - 4; ++i) {
        int j = i + rand() % (argc - 4 - i);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < argc - 4; ++i) {
        if ((indices[i] - 3) % 2 != 0) {
            for (unsigned int j = 0; argv[indices[i]][j] != '\0'; j++) {
                result[k++] = argv[indices[i]][j];
            }
        }
    }
    result[total_len] = '\0';
    free(indices);
    return result;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-l|-r|-u|-n|-c] string [seed [strings...]]\n", argv[0]);
        return 1;
    }

    char* result;
    if (argv[1][0] == '-' && argv[1][1] == 'l') {
        result = string_length(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'r') {
        result = string_reverse(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'u') {
        result = string_toupper_odd(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'n') {
        result = string_sort(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'c') {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s -c seed string1 string2 ...\n", argv[0]);
            return 1;
        }
        result = string_concat_random(argc, argv);
    }
    else {
        fprintf(stderr, "Invalid flag\n");
        return 1;
    }

    printf("Result: %s\n", result);
    free(result);
    return 0;
}