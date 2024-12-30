#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Comparison function for integers (example)
int equalityComparer(int const* a, int const* b) {
    return *a == *b;
}

// Recursive function to generate combinations
void generateCombinations(int* items, size_t items_count, size_t k, int** combinations, size_t* count, int* current_combination, size_t current_index, size_t start_index) {
    if (current_index == k) {
        // Combination of size k is complete, allocate memory and copy it
        int* new_combination = (int*)malloc(sizeof(int) * k);
        if (new_combination == NULL) {
            // Memory allocation error, free allocated memory and exit
            for (size_t i = 0; i < *count; i++) {
                free(combinations[i]);
            }
            free(combinations);
            fprintf(stderr, "Memory allocation error in generateCombinations.\n");
            exit(6); // Exit the program with memory error
        }

        for (size_t i = 0; i < k; i++) {
            new_combination[i] = current_combination[i];
        }
        combinations[*count] = new_combination;
        (*count)++;
        return;
    }

    for (size_t i = start_index; i < items_count; i++) {
        current_combination[current_index] = items[i];
        generateCombinations(items, items_count, k, combinations, count, current_combination, current_index + 1, i + 1);
    }
}

int combinations(int* items, size_t items_count, int*** result_combinations, size_t* result_combinations_count, int (*equality_comparer)(int const*, int const*), size_t k) {
    if (items == NULL) return 1; // Items is NULL
    if (result_combinations == NULL) return 2; // result_combinations is NULL
    if (result_combinations_count == NULL) return 3; // result_combinations_count is NULL
    if (equality_comparer == NULL) return 4; // equality_comparer is NULL
    if (k > items_count) return 5; // k > items_count

    // Check for duplicate elements
    for (size_t i = 0; i < items_count - 1; ++i) {
        for (size_t j = i + 1; j < items_count; ++j) {
            if (equality_comparer(&items[i], &items[j])) {
                return 7; // Duplicate elements found
            }
        }
    }

    // Calculate the number of combinations
    size_t combinations_count = 1;
    for (size_t i = 0; i < k; i++)
    {
        combinations_count *= (items_count - i);
        combinations_count /= (i + 1);
    }

    // Allocate memory for combinations array
    int** combinations_arr = (int**)malloc(sizeof(int*) * combinations_count);
    if (combinations_arr == NULL) {
        return 6; // Memory allocation error
    }

    // Allocate memory for the current combination
    int* current_combination = (int*)malloc(sizeof(int) * k);
    if (current_combination == NULL) {
        free(combinations_arr);
        return 6; // Memory allocation error
    }

    *result_combinations_count = 0;
    generateCombinations(items, items_count, k, combinations_arr, result_combinations_count, current_combination, 0, 0);

    free(current_combination);

    *result_combinations = combinations_arr;
    return 0; // Success
}

int main() {
    int items[] = { 1, 2, 3, 4 };
    size_t itemsCount = sizeof(items) / sizeof(items[0]);
    size_t k = 2;
    int** resultCombinations;
    size_t resultCombinationsCount;

    int errorCode = combinations(items, itemsCount, &resultCombinations, &resultCombinationsCount, equalityComparer, k);

    if (errorCode == 0) {
        printf("Combinations:\n");
        for (size_t i = 0; i < resultCombinationsCount; i++) {
            for (size_t j = 0; j < k; j++)
                printf("%d ", resultCombinations[i][j]);
            printf("\n");
            free(resultCombinations[i]);
        }
        free(resultCombinations);
    }
    else {
        fprintf(stderr, "Error: %d\n", errorCode);
    }
    return 0;
}