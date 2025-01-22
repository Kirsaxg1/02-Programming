#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_TOWERS_CAPACITY 10

typedef struct {
    int* layers;
    int layers_count;
} Tower;

void generateTowers(int blocks_count, int allowed_partial_blocks_usage, int allowed_adjacent_layers_blocks_equal_count,
    Tower** towers, size_t* towers_count, size_t* towers_capacity,
    int* current_tower, int current_layer_index, int current_blocks_used, int previous_layer_blocks) {

    if (current_blocks_used > blocks_count) {
        return;
    }

    if ((allowed_partial_blocks_usage == 0 && current_blocks_used == blocks_count) ||
        (allowed_partial_blocks_usage == 1 && current_blocks_used <= blocks_count)) {

        int num_layers = current_layer_index;
        if (num_layers > 0) {

            Tower* new_tower = (Tower*)malloc(sizeof(Tower));
            if (new_tower == NULL) {
                size_t i;
                for (i = 0; i < *towers_count; i++) {
                    free(towers[i]->layers);
                    free(towers[i]);
                }
                free(towers);
                exit(4);
            }

            new_tower->layers = (int*)malloc(sizeof(int) * (num_layers + 1));
            if (new_tower->layers == NULL) {
                size_t i;
                for (i = 0; i < *towers_count; i++) {
                    free(towers[i]->layers);
                    free(towers[i]);
                }
                free(towers);
                free(new_tower);
                exit(4);
            }

            new_tower->layers[0] = num_layers;
            int i;
            for (i = 0; i < num_layers; i++) {
                new_tower->layers[i + 1] = current_tower[i];
            }
            new_tower->layers_count = num_layers;

            towers[*towers_count] = new_tower;
            (*towers_count)++;

            if (*towers_count == *towers_capacity) {
                *towers_capacity *= 2;
                Tower** temp_towers = (Tower**)realloc(*towers, sizeof(Tower*) * (*towers_capacity));
                if (temp_towers == NULL) {
                    // Memory allocation error
                    for (size_t i = 0; i < *towers_count; i++) {
                        free(towers[i]->layers);
                        free(towers[i]);
                    }
                    free(towers);
                    exit(4);
                }
                *towers = temp_towers;
            }
        }
        return;
    }

    for (int blocks_in_layer = 1; blocks_in_layer <= blocks_count; blocks_in_layer++) {
        if (blocks_in_layer < previous_layer_blocks) continue;

        if (allowed_adjacent_layers_blocks_equal_count == 0 && blocks_in_layer == previous_layer_blocks && current_layer_index != 0) continue;

        current_tower[current_layer_index] = blocks_in_layer;

        generateTowers(blocks_count, allowed_partial_blocks_usage, allowed_adjacent_layers_blocks_equal_count,
            towers, towers_count, towers_capacity, current_tower, current_layer_index + 1, current_blocks_used + blocks_in_layer, blocks_in_layer);
    }
}

int towers_construction(int blocks_count, int*** result_towers, size_t* result_towers_count, int allowed_partial_blocks_usage, int allowed_adjacent_layers_blocks_equal_count) {
    // Validate input parameters
    if (result_towers == NULL) return 1;
    if (result_towers_count == NULL) return 2;
    if (blocks_count < 0) return 3;

    Tower** towers = (Tower**)malloc(sizeof(Tower*) * INITIAL_TOWERS_CAPACITY);
    if (towers == NULL) return 4;

    size_t towers_capacity = INITIAL_TOWERS_CAPACITY;
    *result_towers_count = 0;
    int* current_tower = (int*)malloc(sizeof(int) * blocks_count);
    if (current_tower == NULL) {
        free(towers);
        return 4;
    }

    generateTowers(blocks_count, allowed_partial_blocks_usage, allowed_adjacent_layers_blocks_equal_count,
        towers, result_towers_count, &towers_capacity, current_tower, 0, 0, 0);

    free(current_tower);

    *result_towers = (int**)malloc(sizeof(int*) * (*result_towers_count));
    if (*result_towers == NULL) {
        size_t i;
        for (i = 0; i < *result_towers_count; i++) {
            free(towers[i]->layers);
            free(towers[i]);
        }
        free(towers);
        return 4;
    }

    size_t i;
    for (i = 0; i < *result_towers_count; i++) {
        size_t layer_count = towers[i]->layers_count + 1;
        (*result_towers)[i] = (int*)malloc(sizeof(int) * layer_count);
        if ((*result_towers)[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free((*result_towers)[j]);
            }
            free(*result_towers);
            size_t k;
            for (k = 0; k < *result_towers_count; k++) {
                free(towers[k]->layers);
                free(towers[k]);
            }
            free(towers);
            return 4;
        }
        (*result_towers)[i][0] = towers[i]->layers_count;
        for (size_t j = 0; j < towers[i]->layers_count; j++) {
            (*result_towers)[i][j + 1] = towers[i]->layers[j + 1];
        }
        free(towers[i]->layers);
        free(towers[i]);
    }

    free(towers);
    return 0;
}

int main() {
    int blocks_count = 6;
    int** result_towers = NULL;
    size_t result_towers_count = 0;
    int allowed_partial_blocks_usage = 0;
    int allowed_adjacent_layers_blocks_equal_count = 0;

    int errorCode = towers_construction(blocks_count, &result_towers, &result_towers_count, allowed_partial_blocks_usage, allowed_adjacent_layers_blocks_equal_count);

    if (errorCode == 0) {
        printf("Towers configurations (partial = 0, equal = 0):\n");
        size_t i;
        for (i = 0; i < result_towers_count; i++) {
            if (result_towers[i] == NULL) {
                printf("Error: memory allocation failed for tower %zu.\n", i + 1);
                continue;
            }
            printf("Tower %zu: ", i + 1);
            int j;
            for (j = 1; j <= result_towers[i][0]; j++) {
                printf("%d ", result_towers[i][j]);
            }
            printf("\n");
            free(result_towers[i]);
        }
        free(result_towers);
    }
    else {
        switch (errorCode) {
        case 1:
            printf("Error: result_towers is NULL.\n");
            break;
        case 2:
            printf("Error: result_towers_count is NULL.\n");
            break;
        case 3:
            printf("Error: blocks_count is negative.\n");
            break;
        case 4:
            printf("Error: memory allocation failed.\n");
            break;
        default:
            printf("Unknown error: %d\n", errorCode);
            break;
        }
    }

    // Второй тест
    blocks_count = 6;
    allowed_partial_blocks_usage = 1;
    allowed_adjacent_layers_blocks_equal_count = 1;

    errorCode = towers_construction(blocks_count, &result_towers, &result_towers_count, allowed_partial_blocks_usage, allowed_adjacent_layers_blocks_equal_count);

    if (errorCode == 0) {
        printf("Towers configurations (partial = 1, equal = 1):\n");
        size_t i;
        for (i = 0; i < result_towers_count; i++) {
            if (result_towers[i] == NULL) {
                printf("Error: memory allocation failed for tower %zu.\n", i + 1);
                continue;
            }
            printf("Tower %zu: ", i + 1);
            int j;
            for (j = 1; j <= result_towers[i][0]; j++) {
                printf("%d ", result_towers[i][j]);
            }
            printf("\n");
            free(result_towers[i]);
        }
        free(result_towers);
    }
    else {
        switch (errorCode) {
        case 1:
            printf("Error: result_towers is NULL.\n");
            break;
        case 2:
            printf("Error: result_towers_count is NULL.\n");
            break;
        case 3:
            printf("Error: blocks_count is negative.\n");
            break;
        case 4:
            printf("Error: memory allocation failed.\n");
            break;
        default:
            printf("Unknown error: %d\n", errorCode);
            break;
        }
    }

    return 0;
}