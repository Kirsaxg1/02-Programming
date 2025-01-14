#include <stdio.h>
#include <stdlib.h>

typedef int tvalue;

#define SUCCESS 0
#define NULL_SEQUENCE 1
#define NULL_START_INDEX_STORAGE 2
#define NULL_LENGTH_STORAGE 3
#define NULL_COMPARER 4

int find_the_longest_sawtooth_subsequence(tvalue const* sequence, size_t sequence_length,
    size_t* subsequence_start_index_storage, size_t* subsequence_length_storage,
    int (*comparer)(tvalue const*, tvalue const*), int is_comparison_is_strict);

int int_comparer(tvalue const* a, tvalue const* b) {
    return *a - *b;
}

int find_the_longest_sawtooth_subsequence(tvalue const* sequence, size_t sequence_length,
    size_t* subsequence_start_index_storage, size_t* subsequence_length_storage,
    int (*comparer)(tvalue const*, tvalue const*), int is_comparison_is_strict) {

    if (sequence == NULL) return NULL_SEQUENCE;
    if (subsequence_start_index_storage == NULL) return NULL_START_INDEX_STORAGE;
    if (subsequence_length_storage == NULL) return NULL_LENGTH_STORAGE;
    if (comparer == NULL) return NULL_COMPARER;

    *subsequence_start_index_storage = -1;
    *subsequence_length_storage = 0;

    if (sequence_length == 0) {
        return SUCCESS;
    }
    if (sequence_length == 1) {
        *subsequence_start_index_storage = 0;
        *subsequence_length_storage = 1;
        return SUCCESS;
    }

    size_t max_length = 1;
    size_t max_start = 0;

    size_t current_length = 1;
    size_t current_start = 0;

    int direction = 0; 

    for (size_t i = 1; i < sequence_length; i++) {
        int cmp = comparer(&sequence[i - 1], &sequence[i]);

        if (cmp == 0 && is_comparison_is_strict) {
   
            if (current_length > max_length) {
                max_length = current_length;
                max_start = current_start;
            }
            current_length = 1;
            current_start = i;
            direction = 0;
        }
        else if (cmp < 0) {
            if (direction == 1) {
                if (current_length > max_length) {
                    max_length = current_length;
                    max_start = current_start;
                }
                current_length = 2;
                current_start = i - 1;
            }
            else {
                current_length++;
            }
            direction = -1;
        }
        else if (cmp > 0) {
            if (direction == -1) {
                if (current_length > max_length) {
                    max_length = current_length;
                    max_start = current_start;
                }
                current_length = 2;
                current_start = i - 1;
            }
            else {
                current_length++;
            }
            direction = 1;
        }
    }

    if (current_length > max_length) {
        max_length = current_length;
        max_start = current_start;
    }

    *subsequence_start_index_storage = max_start;
    *subsequence_length_storage = max_length;

    return SUCCESS;
}

int main() {

    tvalue sequence[] = { 1, 2, 1, 3, 2, 4, 3, 5, 4, 6 };
    size_t sequence_length = sizeof(sequence) / sizeof(sequence[0]);

    size_t start_index;
    size_t length;

    int result = find_the_longest_sawtooth_subsequence(sequence, sequence_length, &start_index, &length, int_comparer, 1);

    if (result == SUCCESS) {
        printf("Longest sawtooth subsequence starts at index %zu with length %zu:\n", start_index, length);
        for (size_t i = start_index; i < start_index + length; i++) {
            printf("%d ", sequence[i]);
        }
        printf("\n");
    }
    else {
        printf("Error: %d\n", result);
    }

    return 0;
}