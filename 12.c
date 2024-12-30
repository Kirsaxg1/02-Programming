#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

int substr(char* to_find, int case_sensitive, char*** results, int*** positions, size_t* results_count, ...) {

    int err;
    char* str_ptr, * find_ptr;
    int pos = -1;
    int size = 10;
    int** temp_int_ptr_ptr;
    char* temp_str_ptr;
    int current_ans_index = 0;
    int current_position_str_index = 1;
    int current_position_str_size = size;
    int k;

    if (to_find == NULL) return 1;
    if (results == NULL) return 2;
    if (positions == NULL) return 3;
    if (results_count == NULL) return 4;

    va_list ap;
    va_start(ap, results_count);

    *results_count = 0;
    *results = malloc(sizeof(char*) * size);
    if (*results == NULL) {
        va_end(ap);
        return 5;
    }

    *positions = malloc(sizeof(int*) * size);
    if (*positions == NULL) {
        free(*results);
        va_end(ap);
        return 6;
    }

    int current_ans_size = size;

    for (int i = 0; i < current_ans_size; i++) {
        (*positions)[i] = (int*)malloc(size * sizeof(int));
        if ((*positions)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free((*positions)[j]);
            }

            free(*positions);
            free(*results);

            va_end(ap);

            return 7;
        }

        (*positions)[i][0] = 0;

    }

    while ((str_ptr = va_arg(ap, char*)) != NULL) {

        temp_str_ptr = str_ptr;
        k = 0;
        pos = -1;
        current_position_str_index = 1;
        current_position_str_size = size;

        if (current_ans_index >= current_ans_size) {

            size *= 2;
            temp_int_ptr_ptr = realloc(*positions, size * sizeof(int*));

            if (temp_int_ptr_ptr == NULL) {
                for (int i = 0; i < current_ans_index; ++i) {
                    free((*results)[i]);
                }

                free(*results);
                for (int j = 0; j < current_ans_size; j++) {
                    free((*positions)[j]);
                }

                free(*positions);
                va_end(ap);
                return 8;
            }

            *positions = temp_int_ptr_ptr;
            temp_str_ptr = realloc(*results, size * sizeof(char*));
            if (temp_str_ptr == NULL) {

                for (int i = 0; i < current_ans_index; ++i) {
                    free((*results)[i]);
                }
                free(*results);
                for (int j = 0; j < current_ans_size; j++) {
                    free((*positions)[j]);
                }
                free(*positions);
                va_end(ap);
                return 9;
            }
            *results = temp_str_ptr;

            for (int i = current_ans_size; i < size; i++) {
                (*positions)[i] = (int*)malloc(current_position_str_size * sizeof(int));

                if ((*positions)[i] == NULL) {
                    for (int j = 0; j < i; j++) {
                        free((*positions)[j]);
                    }

                    free(*positions);
                    for (int j = 0; j < current_ans_size; ++j) {
                        free((*results)[j]);

                    }
                    free(*results);
                    va_end(ap);
                    return 10;
                }
                (*positions)[i][0] = 0;
            }
            current_ans_size = size;
        }

        find_ptr = to_find;

        while (*str_ptr != '\0') {
            if (case_sensitive == 0 &&
                tolower(*str_ptr) == tolower(*find_ptr)) {
                if (pos == -1) {
                    pos = k;
                }
                find_ptr++;
            }
            else if (*str_ptr == *find_ptr) {
                if (pos == -1) {
                    pos = k;
                }
                find_ptr++;
            }
            else if (*find_ptr == '\0' && pos != -1) {
                if (current_position_str_index >= current_position_str_size) {
                    current_position_str_size *= 2;
                    temp_int_ptr_ptr = realloc((*positions)[current_ans_index], current_position_str_size * sizeof(int));
                    if (temp_int_ptr_ptr == NULL) {
                        for (int i = 0; i < current_ans_index; ++i) {
                            free((*results)[i]);
                        }
                        free(*results);
                        for (int j = 0; j < current_ans_size; j++) {
                            free((*positions)[j]);
                        }
                        free(*positions);
                        va_end(ap);
                        return 11;
                    }
                    (*positions)[current_ans_index] = temp_int_ptr_ptr;
                }
                (*positions)[current_ans_index][current_position_str_index] = pos;
                (*positions)[current_ans_index][0]++;
                current_position_str_index++;
                pos = -1;
                find_ptr = to_find;
            }
            else {
                pos = -1;
                find_ptr = to_find;
            }
            str_ptr++;
            k++;
        }
        if ((*positions)[current_ans_index][0] != 0) {
            size_t len = strlen(temp_str_ptr) + 1;
            (*results)[current_ans_index] = malloc(len);
            if ((*results)[current_ans_index] == NULL) {
                for (int i = 0; i < current_ans_index; ++i) {
                    free((*results)[i]);
                }
                free(*results);
                for (int j = 0; j < current_ans_size; j++) {
                    free((*positions)[j]);
                }
                free(*positions);
                va_end(ap);
                return 12;
            }
            strcpy((*results)[current_ans_index], temp_str_ptr);

            current_ans_index++;
            (*results_count)++;
        }
    }

    va_end(ap);
    return 0;
}

int main() {

    int err, i, j;
    int** pos;
    size_t results_count = 0;
    char* inital = "el";
    char* str1 = "Helloworld";
    char* str2 = "HELLOHEllohelLO";
    char** results = NULL;

    err = substr(inital, 0, &results, &pos, &results_count, str1, str2, NULL);

    if (err) {
        printf("Error code: %d\n", err);
        return err;
    }

    for (i = 0; i < results_count; i++) {
        printf("String: %s\n", results[i]);
        printf("Positions: ");
        for (j = 1; j <= pos[i][0]; j++) {
            printf("%d ", pos[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < results_count; ++i) {
        free(results[i]);
        free(pos[i]);
    }
    free(results);
    free(pos);
    return EXIT_SUCCESS;
}