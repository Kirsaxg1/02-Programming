#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int int_comparer(int const* num1, int const* num2) {
    return *num1 == *num2 ? 0 : 1;
}

void generate_permutations(int* items, size_t items_count, size_t current_index,
    int** result_permutations, size_t* result_index, int* current_permutation, int (*equality_comparer)(int const*, int const*)) {

    if (current_index == items_count) {
        result_permutations[*result_index] = (int*)malloc(items_count * sizeof(int));
        if (result_permutations[*result_index] == NULL) {
            return;
        }
        size_t i;
        for (i = 0; i < items_count; ++i) {
            result_permutations[*result_index][i] = current_permutation[i];
        }
        (*result_index)++;
        return;
    }

    size_t i;
    for (i = 0; i < items_count; ++i) {
        int is_used = 0;
        size_t j;
        for (j = 0; j < current_index; ++j) {
            if (equality_comparer(&items[i], &current_permutation[j]) == 0) {
                is_used = 1;
                break;
            }
        }
        if (!is_used) {
            current_permutation[current_index] = items[i];
            generate_permutations(items, items_count, current_index + 1,
                result_permutations, result_index, current_permutation, equality_comparer);
        }
    }
}

int permutations(int* items, size_t items_count, int*** result_permutations,
    size_t* result_permutations_count, int (*equality_comparer)(int const*, int const*)) {

    if (items == NULL) return 1;
    if (result_permutations == NULL) return 2;
    if (result_permutations_count == NULL) return 3;
    if (equality_comparer == NULL) return 4;

    size_t i, j;
    for (i = 0; i < items_count; ++i) {
        for (j = i + 1; j < items_count; ++j) {
            if (equality_comparer(&items[i], &items[j]) == 0) {
                return 6;
            }
        }
    }

    size_t permutations_count = 1;
    for (i = 1; i <= items_count; ++i) {
        permutations_count *= i;
    }

    *result_permutations = (int**)malloc(permutations_count * sizeof(int*));
    if (*result_permutations == NULL) {
        return 5;
    }

    int* current_permutation = (int*)malloc(items_count * sizeof(int));
    if (current_permutation == NULL) {
        free(*result_permutations);
        return 5;
    }

    size_t result_index = 0;

    generate_permutations(items, items_count, 0, *result_permutations, &result_index, current_permutation, equality_comparer);
    free(current_permutation);

    *result_permutations_count = result_index;

    return 0;
}

int main() {
    int items[] = { 1, 2, 3 };
    size_t items_count = sizeof(items) / sizeof(items[0]);
    int** result_permutations = NULL;
    size_t result_permutations_count = 0;

    int err = permutations(items, items_count, &result_permutations, &result_permutations_count, int_comparer);

    if (err == 0) {
        printf("Found permutations: %zu\n", result_permutations_count);
        size_t i, j;
        for (i = 0; i < result_permutations_count; i++) {
            if (result_permutations[i] == NULL) {
                printf("Error: memory allocation failed for permutation %zu.\n", i);
                continue;
            }
            printf("{");
            for (j = 0; j < items_count; j++) {
                printf("%d%s", result_permutations[i][j], (j == items_count - 1) ? "" : ", ");
            }
            printf("}\n");
        }

        for (i = 0; i < result_permutations_count; i++) {
            if (result_permutations[i] != NULL) {
                free(result_permutations[i]);
            }
        }
        if (result_permutations != NULL) {
            free(result_permutations);
        }
    }
    else {

        if (err == 1) printf("Error: items is NULL.\n");
        else if (err == 2) printf("Error: result_permutations is NULL.\n");
        else if (err == 3) printf("Error: result_permutations_count is NULL.\n");
        else if (err == 4) printf("Error: equality_comparer is NULL.\n");
        else if (err == 5) printf("Error: memory allocation failed.\n");
        else if (err == 6) printf("Error: found not unique elements.\n");
    }

    return 0;
}