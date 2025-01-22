#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int int_comparer(int const* num1, int const* num2) {
    return *num1 == *num2 ? 0 : 1;
}

int subsets(int* items, size_t items_count, int*** result_subsets, size_t* result_subsets_count, int
(*equality_comparer)(int const*, int const*)) {

    if (items == NULL) return 1;
    if (result_subsets == NULL) return 2;
    if (result_subsets_count == NULL) return 3;
    if (equality_comparer == NULL) return 4;

    size_t i, j;
    for (i = 0; i < items_count; ++i) {
        for (j = i + 1; j < items_count; ++j) {
            if (equality_comparer(&items[i], &items[j]) == 0) {
                return 6;
            }
        }
    }

    size_t subsets_count = (size_t)pow(2, items_count);

    *result_subsets = (int**)malloc(subsets_count * sizeof(int*));
    if (*result_subsets == NULL) {
        return 5;
    }

    size_t k; 
    for (i = 0; i < subsets_count; i++) {
        size_t subset_size = 0;

        for (j = 0; j < items_count; j++) {
            if ((i >> j) & 1) {
                subset_size++;
            }
        }

        (*result_subsets)[i] = (int*)malloc((subset_size + 1) * sizeof(int));
        if ((*result_subsets)[i] == NULL) {
            for (k = 0; k < i; k++) {
                free((*result_subsets)[k]);
            }
            free(*result_subsets);
            return 5;
        }

        (*result_subsets)[i][0] = subset_size;

        size_t index = 1;
        for (j = 0; j < items_count; j++) {
            if ((i >> j) & 1) {
                (*result_subsets)[i][index] = items[j];
                index++;
            }
        }
    }

    *result_subsets_count = subsets_count;
    return 0;
}

int main() {
    int items[] = { 1, 2, 3 };
    size_t items_count = sizeof(items) / sizeof(items[0]);
    int** result_subsets = NULL;
    size_t result_subsets_count = 0;

    int err = subsets(items, items_count, &result_subsets, &result_subsets_count, int_comparer);

    if (err == 0) {
        printf("Found subsets: %zu\n", result_subsets_count);
        size_t i, j;
        for (i = 0; i < result_subsets_count; i++) {
            if (result_subsets[i] == NULL) {
                printf("Error: memory allocation failed for subset %zu.\n", i);
                continue;
            }
            printf("{");
            for (j = 1; j <= result_subsets[i][0]; j++) {
                printf("%d%s", result_subsets[i][j], (j == result_subsets[i][0]) ? "" : ", ");
            }
            printf("}\n");
        }

        for (i = 0; i < result_subsets_count; i++) {
            if (result_subsets[i] != NULL) {
                free(result_subsets[i]);
            }
        }
        if (result_subsets != NULL) {
            free(result_subsets);
        }
    }
    else {
        if (err == 1) printf("Error: items is NULL.\n");
        else if (err == 2) printf("Error: result_subsets is NULL.\n");
        else if (err == 3) printf("Error: result_subsets_count is NULL.\n");
        else if (err == 4) printf("Error: equality_comparer is NULL.\n");
        else if (err == 5) printf("Error: memory allocation failed.\n");
        else if (err == 6) printf("Error: found not unique elements.\n");
    }

    return 0;
}