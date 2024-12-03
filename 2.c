#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <ctype.h>
//#include <stdlib.h>
//
//char *COUNT_LENGTH(char* str)
//{
//	int length = 0;
//
//	char* result = (char*)malloc(sizeof(char)*20);
//	while (str[length] != '\0') length++;
//
//	sprintf(result, "%d", length);
//	return result;
//}
//
//char *STR_REVERSED(char* str)
//{
//	int length = 0;
//	while (str[length] != '\0') length++;
//
//	char* result = (char*)malloc((length + 1) * (sizeof(char)));
//	for (int i = 0; i < length; i++)
//	{
//		result[i] = str[length - i - 1];
//	}
//	result[length] = '\0';
//	return result;
//}
//
//char *UPPER_CASE(char* str)
//{
//	int length = 0;
//	while (str[length] != '\0') length++;
//
//	char* result = (char*)malloc((length + 1) * (sizeof(char)));
//	for (int i = 0; i < length; i++)
//	{
//		if (i % 2 != 0)
//		{
//			result[i] = toupper(str[i]);
//		} else 
//		{
//			result[i] = str[i];
//		}
//	}
//	result[length] = '\0';
//	return result;
//}
//
//char *TRANSFORMATION_STR(char* str)
//{
//	int length = 0;
//	while (str[length] != '\0') length++;
//
//	char* numbers = (char*)malloc((length ) * (sizeof(char)));
//	char* letteres = (char*)malloc((length ) * (sizeof(char)));
//	char* other = (char*)malloc((length ) * (sizeof(char)));
//	int N_count = 0, T_count = 0, O_count = 0;
//
//	for (int i = 0; i < length; i++)
//	{
//		if (isdigit(str[i]))
//		{
//			numbers[N_count++] = str[i];
//		} 
//		else if (isalpha(str[i]))
//		{
//			letteres[T_count++] = str[i];
//		}
//		else
//		{
//			other[O_count++] = str[i];
//		}
//	}
//
//	numbers[N_count] = '\0';
//	letteres[T_count] = '\0';
//	other[O_count] = '\0';
//
//	char* result = (char*)malloc((length + 1) * (sizeof(char)));
//	sprintf(result, "%s%s%s", numbers, letteres, other);
//
//	free(numbers);
//	free(letteres);
//	free(other);
//
//	return result;
//}
//
//char* CONCATENATION_STR(int seed, char** strings, int num_strings)
//{
//	srand(seed);
//	char* result = (char*)malloc(sizeof(char)*100);
//	result[0] = '\0';
//
//	//int* used = (int*)malloc(num_strings * sizeof(int));
//	for (int i = 1; i < num_strings; i++)
//	{
//		int index = rand() % num_strings;
//		strcat(result, strings[index]);
//	} 
//
//	return result;
//}
//
//int main(int argc, char* argv[]) {
//	
//	if (argc < 3) {
//		printf("Not enough arguments provided");
//		return 1;
//	}
//
//	char* flag = argv[1];
//	char* input_str = argv[2];
//
//	char* result;
//
//	if (strcmp(flag, "-l") == 0) {
//		result = COUNT_LENGTH(input_str);
//	}
//	else if (strcmp(flag, "-r") == 0) {
//		result = STR_REVERSED(input_str);
//	}
//	else if (strcmp(flag, "-u") == 0) {
//		result = UPPER_CASE(input_str);
//	}
//	else if (strcmp(flag, "-n") == 0) {
//		result = TRANSFORMATION_STR(input_str);
//	}
//	else if (strcmp(flag, "-c") == 0) {
//		if (argc < 4) {
//			printf("Not enough arguments provided for -c flag");
//			return 1;
//		}
//		int seed = atoi(argv[3]);
//		result = CONCATENATION_STR(seed, argc - 4, &argv[4]);
//	}
//	else {
//		printf("Unknown flag");
//		return 1;
//	}
//
//	printf("Result: %s\n", result);
//
//	free(result);
//
//	return 0;
//}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Функция для подсчета длины строки
char* string_length(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* result = (char*)malloc(sizeof(char) * (12 + 1)); // 12 достаточно для большинства чисел
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    sprintf(result, "%u", len);
    return result;
}

// Функция для обращения строки
char* string_reverse(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* result = (char*)malloc(sizeof(char) * (len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (unsigned int i = 0; i < len; i++) {
        result[i] = str[len - 1 - i];
    }
    result[len] = '\0';
    return result;
}

// Функция для преобразования символов на нечетных позициях в верхний регистр
char* string_toupper_odd(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* result = (char*)malloc(sizeof(char) * (len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (unsigned int i = 0; i < len; i++) {
        result[i] = (i % 2 != 0) ? toupper(str[i]) : str[i];
    }
    result[len] = '\0';
    return result;
}

// Функция для сортировки символов строки
char* string_sort(const char* str) {
    unsigned int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    char* digits = (char*)malloc(sizeof(char) * (len + 1));
    char* letters = (char*)malloc(sizeof(char) * (len + 1));
    char* others = (char*)malloc(sizeof(char) * (len + 1));
    unsigned int digit_count = 0;
    unsigned int letter_count = 0;
    unsigned int other_count = 0;
    for (unsigned int i = 0; i < len; i++) {
        if (isdigit(str[i])) {
            digits[digit_count++] = str[i];
        }
        else if (isalpha(str[i])) {
            letters[letter_count++] = str[i];
        }
        else {
            others[other_count++] = str[i];
        }
    }
    digits[digit_count] = '\0';
    letters[letter_count] = '\0';
    others[other_count] = '\0';

    unsigned int total_len = digit_count + letter_count + other_count;
    char* result = (char*)malloc(sizeof(char) * (total_len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    unsigned int k = 0;
    for (unsigned int i = 0; i < digit_count; i++, k++) {
        result[k] = digits[i];
    }
    for (unsigned int i = 0; i < letter_count; i++, k++) {
        result[k] = letters[i];
    }
    for (unsigned int i = 0; i < other_count; i++, k++) {
        result[k] = others[i];
    }
    result[total_len] = '\0';

    free(digits);
    free(letters);
    free(others);
    return result;
}

// Функция для конкатенации строк в псевдослучайном порядке
char* string_concat_random(int argc, char* argv[]) {
    unsigned int seed = (unsigned int)atoi(argv[3]);
    srand(seed);

    unsigned int total_len = 0;
    for (int i = 4; i < argc; i++) {
        if ((i - 3) % 2 != 0) {
            unsigned int len = 0;
            while (argv[i][len] != '\0') {
                len++;
            }
            total_len += len;
        }
    }

    char* result = (char*)malloc(sizeof(char) * (total_len + 1));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    unsigned int k = 0;
    int* indices = (int*)malloc(sizeof(int) * (argc - 4));
    for (int i = 0; i < argc - 4; ++i) {
        indices[i] = i + 4;
    }

    for (int i = 0; i < argc - 4; ++i) {
        int j = i + rand() % (argc - 4 - i);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < argc - 4; ++i) {
        if ((indices[i] - 3) % 2 != 0) {
            for (unsigned int j = 0; argv[indices[i]][j] != '\0'; j++) {
                result[k++] = argv[indices[i]][j];
            }
        }
    }
    result[total_len] = '\0';
    free(indices);
    return result;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [-l|-r|-u|-n|-c] string [seed [strings...]]\n", argv[0]);
        return 1;
    }

    char* result;
    if (argv[1][0] == '-' && argv[1][1] == 'l') {
        result = string_length(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'r') {
        result = string_reverse(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'u') {
        result = string_toupper_odd(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'n') {
        result = string_sort(argv[2]);
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'c') {
        if (argc < 4) {
            fprintf(stderr, "Usage: %s -c seed string1 string2 ...\n", argv[0]);
            return 1;
        }
        result = string_concat_random(argc, argv);
    }
    else {
        fprintf(stderr, "Invalid flag\n");
        return 1;
    }

    printf("Result: %s\n", result);
    free(result);
    return 0;
}