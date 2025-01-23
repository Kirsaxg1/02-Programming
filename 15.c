//#include <stdio.h>
//#include <stdlib.h>
//
//typedef int tvalue;
//
//#define SUCCESS 0
//#define NULL_MATRIX 1
//#define NULL_MATRIX_ROW 2
//#define NULL_SADDLE_POINTS_STORAGE 3
//#define NULL_SADDLE_POINTS_COUNT_STORAGE 4
//#define NULL_COMPARER 5
//#define MEMORY_ERROR 6
//
//int find_saddle_points(tvalue const* const* matrix, size_t matrix_rows_count, size_t matrix_columns_count,
//    size_t*** found_saddle_points_storage, size_t* found_saddle_points_count_storage,
//    int (*comparer)(tvalue const*, tvalue const*), int is_comparison_is_strict);
//
//int int_comparer(tvalue const* a, tvalue const* b) {
//    return *a - *b;
//}
//
//int find_saddle_points(tvalue const* const* matrix, size_t matrix_rows_count, size_t matrix_columns_count,
//    size_t*** found_saddle_points_storage, size_t* found_saddle_points_count_storage,
//    int (*comparer)(tvalue const*, tvalue const*), int is_comparison_is_strict) {
//
//    if (matrix == NULL) return NULL_MATRIX;
//    for (size_t i = 0; i < matrix_rows_count; i++) {
//        if (matrix[i] == NULL) return NULL_MATRIX_ROW;
//    }
//    if (found_saddle_points_storage == NULL) return NULL_SADDLE_POINTS_STORAGE;
//    if (found_saddle_points_count_storage == NULL) return NULL_SADDLE_POINTS_COUNT_STORAGE;
//    if (comparer == NULL) return NULL_COMPARER;
//
//    *found_saddle_points_storage = NULL;
//    *found_saddle_points_count_storage = 0;
//
//    if (matrix_rows_count == 0 || matrix_columns_count == 0) {
//        return SUCCESS;
//    }
//
//    size_t* min_in_rows = malloc(matrix_rows_count * sizeof(size_t));
//    size_t* max_in_columns = malloc(matrix_columns_count * sizeof(size_t));
//
//    if (min_in_rows == NULL || max_in_columns == NULL) {
//        free(min_in_rows);
//        free(max_in_columns);
//        return MEMORY_ERROR;
//    }
//
//    for (size_t i = 0; i < matrix_rows_count; i++) {
//        min_in_rows[i] = 0;
//        for (size_t j = 1; j < matrix_columns_count; j++) {
//            if (comparer(&matrix[i][j], &matrix[i][min_in_rows[i]]) < 0) {
//                min_in_rows[i] = j;
//            }
//        }
//    }
//
//    for (size_t j = 0; j < matrix_columns_count; j++) {
//        max_in_columns[j] = 0;
//        for (size_t i = 1; i < matrix_rows_count; i++) {
//            if (comparer(&matrix[i][j], &matrix[max_in_columns[j]][j]) > 0) {
//                max_in_columns[j] = i;
//            }
//        }
//    }
//
//    size_t saddle_points_count = 0;
//    for (size_t i = 0; i < matrix_rows_count; i++) {
//        for (size_t j = 0; j < matrix_columns_count; j++) {
//            if (min_in_rows[i] == j && max_in_columns[j] == i) {
//                saddle_points_count++;
//            }
//        }
//    }
//
//    *found_saddle_points_storage = malloc(saddle_points_count * sizeof(size_t*));
//    if (*found_saddle_points_storage == NULL) {
//        free(min_in_rows);
//        free(max_in_columns);
//        return MEMORY_ERROR;
//    }
//
//    for (size_t i = 0; i < saddle_points_count; i++) {
//        (*found_saddle_points_storage)[i] = malloc(2 * sizeof(size_t));
//        if ((*found_saddle_points_storage)[i] == NULL) {
//            for (size_t k = 0; k < i; k++) {
//                free((*found_saddle_points_storage)[k]);
//            }
//            free(*found_saddle_points_storage);
//            free(min_in_rows);
//            free(max_in_columns);
//            return MEMORY_ERROR;
//        }
//    }
//
//    size_t index = 0;
//    for (size_t i = 0; i < matrix_rows_count; i++) {
//        for (size_t j = 0; j < matrix_columns_count; j++) {
//            if (min_in_rows[i] == j && max_in_columns[j] == i) {
//                (*found_saddle_points_storage)[index][0] = i;
//                (*found_saddle_points_storage)[index][1] = j;
//                index++;
//            }
//        }
//    }
//
//    *found_saddle_points_count_storage = saddle_points_count;
//
//    free(min_in_rows);
//    free(max_in_columns);
//
//    return SUCCESS;
//}
//
//int main() {
// 
//    tvalue matrix[3][3] = {
//        {1, 2, 3},
//        {4, 5, 6},
//        {7, 8, 9}
//    };
//
//    tvalue* matrix_ptrs[3] = { matrix[0], matrix[1], matrix[2] };
//
//    size_t** saddle_points = NULL;
//    size_t saddle_points_count = 0;
//
//    int result = find_saddle_points(matrix_ptrs, 3, 3, &saddle_points, &saddle_points_count, int_comparer, 1);
//
//    if (result == SUCCESS) {
//        printf("Found %zu saddle points:\n", saddle_points_count);
//        for (size_t i = 0; i < saddle_points_count; i++) {
//            printf("(%zu, %zu)\n", saddle_points[i][0], saddle_points[i][1]);
//        }
//
//        for (size_t i = 0; i < saddle_points_count; i++) {
//            free(saddle_points[i]);
//        }
//        free(saddle_points);
//    }
//    else {
//        printf("Error: %d\n", result);
//    }
//
//    return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int tvalue;

#define SUCCESS 0
#define NULL_MATRIX 1
#define NULL_MATRIX_ROW 2
#define NULL_SADDLE_POINTS_STORAGE 3
#define NULL_SADDLE_POINTS_COUNT_STORAGE 4
#define NULL_COMPARER 5
#define MEMORY_ERROR 6

int find_saddle_points(tvalue const* const* matrix, size_t matrix_rows_count, size_t matrix_columns_count,
    size_t*** found_saddle_points_storage, size_t* found_saddle_points_count_storage,
    int (*comparer)(tvalue const*, tvalue const*), int is_comparison_is_strict);

int int_comparer(tvalue const* a, tvalue const* b) {
    return *a - *b;
}

int find_saddle_points(tvalue const* const* matrix, size_t matrix_rows_count, size_t matrix_columns_count,
    size_t*** found_saddle_points_storage, size_t* found_saddle_points_count_storage,
    int (*comparer)(tvalue const*, tvalue const*), int is_comparison_is_strict) {

    if (matrix == NULL) return NULL_MATRIX;
    size_t i, j, k;
    for (i = 0; i < matrix_rows_count; i++) {
        if (matrix[i] == NULL) return NULL_MATRIX_ROW;
    }
    if (found_saddle_points_storage == NULL) return NULL_SADDLE_POINTS_STORAGE;
    if (found_saddle_points_count_storage == NULL) return NULL_SADDLE_POINTS_COUNT_STORAGE;
    if (comparer == NULL) return NULL_COMPARER;

    *found_saddle_points_storage = NULL;
    *found_saddle_points_count_storage = 0;

    if (matrix_rows_count == 0 || matrix_columns_count == 0) {
        return SUCCESS;
    }

    size_t* min_in_rows = (size_t*)malloc(matrix_rows_count * sizeof(size_t));
    size_t* max_in_columns = (size_t*)malloc(matrix_columns_count * sizeof(size_t));

    if (min_in_rows == NULL || max_in_columns == NULL) {
        free(min_in_rows);
        free(max_in_columns);
        return MEMORY_ERROR;
    }

    for (i = 0; i < matrix_rows_count; i++) {
        min_in_rows[i] = 0;
        for (j = 1; j < matrix_columns_count; j++) {
            if (comparer(&matrix[i][j], &matrix[i][min_in_rows[i]]) < 0) {
                min_in_rows[i] = j;
            }
        }
    }

    for (j = 0; j < matrix_columns_count; j++) {
        max_in_columns[j] = 0;
        for (i = 1; i < matrix_rows_count; i++) {
            if (comparer(&matrix[i][j], &matrix[max_in_columns[j]][j]) > 0) {
                max_in_columns[j] = i;
            }
        }
    }

    size_t saddle_points_count = 0;
    for (i = 0; i < matrix_rows_count; i++) {
        for (j = 0; j < matrix_columns_count; j++) {
            if (min_in_rows[i] == j && max_in_columns[j] == i) {
                saddle_points_count++;
            }
        }
    }

    *found_saddle_points_storage = malloc(saddle_points_count * sizeof(size_t*));
    if (*found_saddle_points_storage == NULL) {
        free(min_in_rows);
        free(max_in_columns);
        return MEMORY_ERROR;
    }

    for (i = 0; i < saddle_points_count; i++) {
        (*found_saddle_points_storage)[i] = (size_t*)malloc(2 * sizeof(size_t));
        if ((*found_saddle_points_storage)[i] == NULL) {
            for (k = 0; k < i; k++) {
                free((*found_saddle_points_storage)[k]);
            }
            free(*found_saddle_points_storage);
            free(min_in_rows);
            free(max_in_columns);
            return MEMORY_ERROR;
        }
    }

    size_t index = 0;
    for (i = 0; i < matrix_rows_count; i++) {
        for (j = 0; j < matrix_columns_count; j++) {
            if (min_in_rows[i] == j && max_in_columns[j] == i) {
                (*found_saddle_points_storage)[index][0] = i;
                (*found_saddle_points_storage)[index][1] = j;
                index++;
            }
        }
    }

    *found_saddle_points_count_storage = saddle_points_count;

    free(min_in_rows);
    free(max_in_columns);

    return SUCCESS;
}

int main() {
    size_t rows, cols;

    printf("Enter the number of rows: ");
    scanf("%zu", &rows);
    printf("Enter the number of columns: ");
    scanf("%zu", &cols);

    tvalue** matrix = malloc(rows * sizeof(tvalue*));
    if (matrix == NULL) {
        printf("Memory allocation failed for matrix rows.\n");
        return 1;
    }

    size_t i, j;
    for (i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(tvalue));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed for matrix columns.\n");
            for (size_t k = 0; k < i; k++) {
                free(matrix[k]);
            }
            free(matrix);
            return 1;
        }
    }

    printf("Enter the matrix elements:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("matrix[%zu][%zu]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    size_t** saddle_points = NULL;
    size_t saddle_points_count = 0;

    int result = find_saddle_points((tvalue const* const*)matrix, rows, cols, &saddle_points, &saddle_points_count, int_comparer, 1);

    if (result == SUCCESS) {
        printf("Found %zu saddle points:\n", saddle_points_count);
        for (i = 0; i < saddle_points_count; i++) {
            printf("(%zu, %zu)\n", saddle_points[i][0], saddle_points[i][1]);
        }

        for (i = 0; i < saddle_points_count; i++) {
            free(saddle_points[i]);
        }
        free(saddle_points);
    }
    else {
        printf("Error: %d\n", result);
    }

    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}