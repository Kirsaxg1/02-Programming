#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define NULL_RESULT_DECOMPOSITIONS 1
#define NULL_RESULT_DECOMPOSITIONS_COUNT 2
#define INVALID_VALUE 3
#define MEMORY_ERROR 4

int sums_decomposition(int value, int*** result_decompositions, size_t* result_decompositions_count, int allowed_equal_sum_components);
void decompose(int current_value, int* current_decomposition, int current_decomposition_size, int allowed_equal,
    int*** result_decompositions, size_t* result_decompositions_count, int max_val);

int sums_decomposition(int value, int*** result_decompositions, size_t* result_decompositions_count, int allowed_equal_sum_components) {
    if (result_decompositions == NULL) return NULL_RESULT_DECOMPOSITIONS;
    if (result_decompositions_count == NULL) return NULL_RESULT_DECOMPOSITIONS_COUNT;
    if (value <= 0) return INVALID_VALUE;

    *result_decompositions_count = 0;
    *result_decompositions = NULL;

    int* current_decomposition = malloc(sizeof(int));
    if (current_decomposition == NULL) return MEMORY_ERROR;

    current_decomposition[0] = 0;
    decompose(value, current_decomposition, 1, allowed_equal_sum_components, result_decompositions, result_decompositions_count, allowed_equal_sum_components ? value : value);
    free(current_decomposition);
    return SUCCESS;
}

void decompose(int current_value, int* current_decomposition, int current_decomposition_size, int allowed_equal,
    int*** result_decompositions, size_t* result_decompositions_count, int max_val) {

    if (current_value < 0) return;
    if (current_value == 0) {
        int* result_decomposition = malloc(sizeof(int) * (current_decomposition_size));
        if (result_decomposition == NULL) return;
        for (int i = 0; i < current_decomposition_size; i++) {
            result_decomposition[i] = current_decomposition[i];
        }
        if (*result_decompositions == NULL) {
            *result_decompositions = malloc(sizeof(int*));
            if (*result_decompositions == NULL) {
                free(result_decomposition);
                return;
            }
        }
        else {
            int** temp_result_decompositions = realloc(*result_decompositions, sizeof(int*) * (*result_decompositions_count + 1));
            if (temp_result_decompositions == NULL) {
                free(result_decomposition);
                return;
            }
            *result_decompositions = temp_result_decompositions;
        }
        (*result_decompositions)[*result_decompositions_count] = result_decomposition;
        (*result_decompositions_count)++;
        return;
    }

    int start = 1;
    int end = allowed_equal ? current_value : current_value < max_val ? current_value : max_val;
    for (int i = start; i <= end; i++) {
        int* new_decomposition = realloc(current_decomposition, sizeof(int) * (current_decomposition_size + 1));
        if (new_decomposition == NULL) return;
        new_decomposition[current_decomposition_size] = i;
        decompose(current_value - i, new_decomposition, current_decomposition_size + 1, allowed_equal, result_decompositions, result_decompositions_count, max_val);
    }

}