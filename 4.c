#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    char* filename; 
    int line_num;  
    int position;   
} SubstringMatch;

int find_substring(const char* str, const char* substr, int start_pos) {
    if (str == NULL || substr == NULL) {
        return -1; 
    }

    int i = start_pos;
    int j = 0;

    while (str[i] != '\0' && substr[j] != '\0') {
        if (str[i] == substr[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1; 
            j = 0;         
        }
    }

    if (substr[j] == '\0') {
        return i - j;
    }

    return -1;
}


int search_in_file(const char* filename, const char* substring, SubstringMatch** matches, int* match_count) {
    if (filename == NULL || substring == NULL || matches == NULL || match_count == NULL) {
        return -1;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1;
    }

    char line[1024];
    int line_num = 1;

    while (fgets(line, sizeof(line), file) != NULL) {
        int pos = 0;
        while (1) {
            int found_pos = find_substring(line, substring, pos);
            if (found_pos == -1) {
                break; 
            }

            (*matches)[*match_count].filename = (char*)malloc((strlen(filename) + 1) * sizeof(char));
            if ((*matches)[*match_count].filename == NULL) {
                fclose(file);
                return -1;
            }
            strcpy((*matches)[*match_count].filename, filename);
            (*matches)[*match_count].line_num = line_num;
            (*matches)[*match_count].position = found_pos + 1;
            (*match_count)++;

            if (*match_count % 100 == 0) {
                SubstringMatch* new_matches = (SubstringMatch*)realloc(*matches, (*match_count + 100) * sizeof(SubstringMatch));
                if (new_matches == NULL) {
                    fclose(file);
                    return -1; 
                }
                *matches = new_matches;
            }

            pos = found_pos + 1; 
        }
        line_num++;
    }

    fclose(file);
    return 0; 
}

int search_substring_in_files(const char* substring, SubstringMatch** matches, int* match_count, int num_files, ...) {
    if (substring == NULL || matches == NULL || match_count == NULL || num_files < 1) {
        return -1;
    }

    va_list args;
    va_start(args, num_files);

    *matches = (SubstringMatch*)malloc(100 * sizeof(SubstringMatch));
    if (*matches == NULL) {
        va_end(args);
        return -1;
    }
    *match_count = 0;
    int i;
    for (i = 0; i < num_files; i++) {
        const char* filename = va_arg(args, const char*);
        if (search_in_file(filename, substring, matches, match_count) != 0) {
            va_end(args);
            int j;
            for (j = 0; j < *match_count; j++) {
                free((*matches)[j].filename);
            }
            free(*matches);
            return -1;
        }
    }

    va_end(args);
    return 0; 
}

void free_matches(SubstringMatch* matches, int match_count) {
    int i;
    for (i = 0; i < match_count; i++) {
        free(matches[i].filename);
    }
    free(matches); 
}

int main() {

    const char* substring = "test";
    SubstringMatch* matches = NULL;
    int match_count = 0;

    int status = search_substring_in_files(substring, &matches, &match_count, 2, "C:\\Users\\GIGABYTE\\Desktop\\file1.txt", "C:\\Users\\GIGABYTE\\Desktop\\file2.txt");

    if (status == 0 && matches != NULL) {
        int i;
        for (i = 0; i < match_count; i++) {
            printf("File: %s, Line: %d, Position: %d\n", matches[i].filename, matches[i].line_num, matches[i].position);
        }
        free_matches(matches, match_count); 
    } else {
        printf("Error occurred during search\n");
    }

 
    const char* empty_substring = "";
    matches = NULL;
    match_count = 0;

    status = search_substring_in_files(empty_substring, &matches, &match_count, 1, "C:\\Users\\GIGABYTE\\Desktop\\file1.txt");

    if (status == 0 && matches != NULL) {
        int i;
        for (i = 0; i < match_count; i++) {
            printf("File: %s, Line: %d, Position: %d\n", matches[i].filename, matches[i].line_num, matches[i].position);
        }
        free_matches(matches, match_count); 
    } else {
        printf("Error occurred during search\n");
    }

    return 0;
}