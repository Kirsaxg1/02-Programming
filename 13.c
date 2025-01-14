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
    int*** result_decompositions, size_t* result_decompositions_count, int start);

int sums_decomposition(int value, int*** result_decompositions, size_t* result_decompositions_count, int allowed_equal_sum_components) {
  
    if (result_decompositions == NULL) return NULL_RESULT_DECOMPOSITIONS;
    if (result_decompositions_count == NULL) return NULL_RESULT_DECOMPOSITIONS_COUNT;
    if (value <= 0) return INVALID_VALUE;

    *result_decompositions_count = 0;
    *result_decompositions = NULL;

    int* current_decomposition = malloc(sizeof(int));
    if (current_decomposition == NULL) return MEMORY_ERROR;

    decompose(value, current_decomposition, 0, allowed_equal_sum_components, result_decompositions, result_decompositions_count, 1);

    free(current_decomposition);
    return SUCCESS;
}


void decompose(int current_value, int* current_decomposition, int current_decomposition_size, int allowed_equal,
    int*** result_decompositions, size_t* result_decompositions_count, int start) {

    if (current_value == 0) {

        int* result_decomposition = malloc(sizeof(int) * (current_decomposition_size + 1));
        if (result_decomposition == NULL) return;

        result_decomposition[0] = current_decomposition_size;

        for (int i = 0; i < current_decomposition_size; i++) {
            result_decomposition[i + 1] = current_decomposition[i];
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

    for (int i = start; i <= current_value; i++) {
   
        if (!allowed_equal && i == start && current_decomposition_size > 0 && current_decomposition[current_decomposition_size - 1] == i) {
            continue;
        }

        int* new_decomposition = malloc(sizeof(int) * (current_decomposition_size + 1));
        if (new_decomposition == NULL) return;

        for (int j = 0; j < current_decomposition_size; j++) {
            new_decomposition[j] = current_decomposition[j];
        }

        new_decomposition[current_decomposition_size] = i;
        decompose(current_value - i, new_decomposition, current_decomposition_size + 1, allowed_equal, result_decompositions, result_decompositions_count, i);

        free(new_decomposition);
    }
}
int main() {
    int** decompositions = NULL;
    size_t decompositions_count = 0;

    int value = 5;
    int allowed_equal = 1; 

    int result = sums_decomposition(value, &decompositions, &decompositions_count, allowed_equal);

    if (result == SUCCESS) {
        printf("Found %zu decompositions:\n", decompositions_count);
        for (size_t i = 0; i < decompositions_count; i++) {
            printf("Decomposition %zu: ", i + 1);
            for (int j = 1; j <= decompositions[i][0]; j++) {
                printf("%d ", decompositions[i][j]);
            }
            printf("\n");
            free(decompositions[i]); 
        }
        free(decompositions); 
    }
    else {
        printf("Error: %d\n", result);
    }

    return 0;
}