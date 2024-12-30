#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MATRIX_SIZE (5)
//#define INITIAL_CAPACITY (16)

typedef int tvalue;

int comparer_for_saddle_points(tvalue const* first, tvalue const* second);

int find_saddle_points(tvalue const* const* matrix, size_t matrix_rows_count,
    size_t matrix_columns_count,
    tvalue*** found_saddle_points_storage,
    size_t* found_saddle_points_count_storage,
    int (*comparer)(tvalue const*, tvalue const*),
    int is_comparison_is_strict) {

    size_t i, j, k, current_capacity = 20;
    int comparer_result = 0, is_saddle = 1, err = 0;

    if (matrix == NULL) return 1;
    if (*matrix == NULL) return 2;
    if (found_saddle_points_storage == NULL) return 3;
    if (found_saddle_points_count_storage == NULL) return 4;
    if (comparer == NULL) return 5;

    *found_saddle_points_storage = (tvalue**)malloc(sizeof(tvalue*) * current_capacity);
    if (*found_saddle_points_storage == NULL) return 5;

    for (i = 0; i < matrix_rows_count; i++) {
        for (j = 0; j < matrix_columns_count; j++) {
            is_saddle = 1;

            for (k = 0; k < matrix_rows_count; k++) {
                if (k != i && !(is_comparison_is_strict ? comparer(&matrix[i][j], &matrix[k][j]) > 0 : comparer(&matrix[i][j], &matrix[k][j]) >= 0)) {
                    is_saddle = 0;
                    break;
                }
            }
            if (is_saddle) {
                for (k = 0; k < matrix_rows_count; k++) {
                    if (k != j && !(is_comparison_is_strict ? comparer(&matrix[i][j], &matrix[i][k]) < 0 : comparer(&matrix[i][j], &matrix[i][k]) <= 0)) {
                        is_saddle = 0;
                        break;
                    }
                }
                if (is_saddle) {
                    if (*found_saddle_points_count_storage + 1 >= current_capacity) {
                        err = realloc((void**)found_saddle_points_storage, current_capacity * 2 * sizeof(tvalue*));
                        if (err) {
                            return err;
                        }
                        current_capacity *= 2;
                    }
                    (*found_saddle_points_storage)[(
                        *found_saddle_points_count_storage)] = (tvalue*)malloc(2 * sizeof(tvalue));
                    if((*found_saddle_points_storage)[(*found_saddle_points_count_storage)] == NULL) {
                        return 1;
                    }
                    (*found_saddle_points_storage)[(
                        *found_saddle_points_count_storage)][0] = i;
                    (*found_saddle_points_storage)[(
                        *found_saddle_points_count_storage)][1] = j;
                    (*found_saddle_points_count_storage)++;
                }
            }
        }
    }
    return 0;
}
int comparer_for_saddle_points(tvalue const* first, tvalue const* second) {
    return *first - *second;
}
