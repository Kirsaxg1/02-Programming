#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int tvalue;

int find_the_longest_sawtooth_subsequence(
    tvalue const* sequence, size_t sequence_length,
    size_t* subsequence_start_index_storage, size_t* subsequence_length_storage,
    int (*comparer)(tvalue const*, tvalue const*),
    int is_comparison_is_strict) {

    int is_current_element_sawtooth = 0, left = 0, right = 0;
    int is_sawtooth_element_condition = 0;
    size_t i, current_sabtooth_length = 0, current_sabtooth_start_index = -1;

    *subsequence_length_storage = 0;
    *subsequence_start_index_storage = -1;

    for (i = 0; i < sequence_length; i++) {
        if (is_current_element_sawtooth == 0) {
            current_sabtooth_start_index = i;
        }
        if(i == 0) {
            right = comparer(sequence + i, sequence + i + 1);
            left = right;
        }
        else if (i == sequence_length - 1) {
            left = comparer(sequence + i, sequence + i - 1);
            right = left;
        }
        else {
            left = comparer(sequence + i, sequence + i - 1);
            right = comparer(sequence + i, sequence + i + 1);
        }
        if (is_comparison_is_strict) {
            is_sawtooth_element_condition = ((right < 0 && left <= 0) || (right > 0 && left > 0));
        }
        else {
            is_sawtooth_element_condition = ((right <= 0 && left <= 0) || (right >= 0 && left >= 0));
        }

        if (is_sawtooth_element_condition) {
            is_sawtooth_element_condition = 1;
            current_sabtooth_length++;
        }
        else {
            is_sawtooth_element_condition = 0;
            if (current_sabtooth_length > *subsequence_length_storage) {
                *subsequence_length_storage = current_sabtooth_length;
                *subsequence_start_index_storage = current_sabtooth_start_index;
                current_sabtooth_length = 0;
            }
        }
    }
    if (current_sabtooth_length > *subsequence_length_storage) {
        *subsequence_length_storage = current_sabtooth_length;
        *subsequence_start_index_storage = current_sabtooth_start_index;
    }
    return 0;
}
int comparer_for_subtooth_sequance(tvalue const* first, tvalue const* second) {
    return *first - *second;
}