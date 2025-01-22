#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int equalityComparer(int const* a, int const* b) {
    return *a == *b;
}

void generateCombinations(int* items, size_t items_count, size_t k, int** combinations, size_t* count, int* current_combination, size_t current_index, size_t start_index) {
    if (current_index == k) {
        int* new_combination = (int*)malloc(sizeof(int) * k);
        if (new_combination == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free(combinations[i]);
            }
            free(combinations);
            fprintf(stderr, "Memory allocation error in generateCombinations.\n");
            exit(6);
        }
        for (size_t i = 0; i < k; i++) {
            new_combination[i] = current_combination[i];
        }
        combinations[*count] = new_combination;
        (*count)++;
        return;
    }

    size_t i;
    for (i = start_index; i < items_count; i++) {
        current_combination[current_index] = items[i];
        generateCombinations(items, items_count, k, combinations, count, current_combination, current_index + 1, i + 1);
    }
}

int combinations(int* items, size_t items_count, int*** result_combinations, size_t* result_combinations_count, int (*equality_comparer)(int const*, int const*), size_t k) {
    if (items == NULL) return 1;
    if (result_combinations == NULL) return 2;
    if (result_combinations_count == NULL) return 3;
    if (equality_comparer == NULL) return 4;
    if (k > items_count) return 5;

    size_t i, j;
    for (i = 0; i < items_count - 1; ++i) {
        for (j = i + 1; j < items_count; ++j) {
            if (equality_comparer(&items[i], &items[j])) {
                return 7;
            }
        }
    }

    size_t combinations_count = 1;
    for (i = 0; i < k; i++) {
        combinations_count *= (items_count - i);
        combinations_count /= (i + 1);
    }

    int** combinations_arr = (int**)malloc(sizeof(int*) * combinations_count);
    if (combinations_arr == NULL) {
        return 6;
    }

    int* current_combination = (int*)malloc(sizeof(int) * k);
    if (current_combination == NULL) {
        free(combinations_arr);
        return 6;
    }

    *result_combinations_count = 0;
    generateCombinations(items, items_count, k, combinations_arr, result_combinations_count, current_combination, 0, 0);

    free(current_combination);

    *result_combinations = combinations_arr;
    return 0;
}

int main() {
    int items[] = { 1, 2, 3, 4 };
    size_t itemsCount = sizeof(items) / sizeof(items[0]);
    size_t k = 2;
    int** resultCombinations = NULL;
    size_t resultCombinationsCount = 0;

    int errorCode = combinations(items, itemsCount, &resultCombinations, &resultCombinationsCount, equalityComparer, k);

    if (errorCode == 0) {
        printf("Found combinations: %zu\n", resultCombinationsCount);
        size_t i, j;
        for (i = 0; i < resultCombinationsCount; i++) {
            if (resultCombinations[i] == NULL) {
                printf("Error: memory allocation failed for combination %zu.\n", i);
                continue;
            }
            printf("{");
            for (j = 0; j < k; j++) {
                printf("%d%s", resultCombinations[i][j], (j == k - 1) ? "" : ", ");
            }
            printf("}\n");
        }

        for (i = 0; i < resultCombinationsCount; i++) {
            if (resultCombinations[i] != NULL) {
                free(resultCombinations[i]);
            }
        }
        if (resultCombinations != NULL) {
            free(resultCombinations);
        }
    }
    else {
        switch (errorCode) {
        case 1:
            printf("Error: items is NULL.\n");
            break;
        case 2:
            printf("Error: result_combinations is NULL.\n");
            break;
        case 3:
            printf("Error: result_combinations_count is NULL.\n");
            break;
        case 4:
            printf("Error: equality_comparer is NULL.\n");
            break;
        case 5:
            printf("Error: k is greater than items_count.\n");
            break;
        case 6:
            printf("Error: memory allocation failed.\n");
            break;
        case 7:
            printf("Error: found not unique elements.\n");
            break;
        default:
            printf("Unknown error: %d\n", errorCode);
            break;
        }
    }

    return 0;
}