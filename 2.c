#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char *COUNT_LENGTH(char* str)
{
	int length = 0;

	char* result = (char*)malloc(sizeof(char));
	while (str[length] != '\0') length++;

	sprintf(result, "%d", length);
	return result;
}

char *STR_REVERSED(char* str)
{
	int length = 0;
	while (str[length] != '\0') length++;

	char* result = (char*)malloc((length + 1) * (sizeof(char)));
	for (int i = 0; i < length; i++)
	{
		result[i] = str[length - i - 1];
	}
	result[length] = '\0';
	return result;
}

char *UPPER_CASE(char* str)
{
	int length = 0;
	while (str[length] != 0) length++;

	char* result = (char*)malloc((length + 1) * (sizeof(char)));
	for (int i = 0; i < length; i++)
	{
		if (i % 2 != 0)
		{
			result[i] = toupper(str[i]);
		} else 
		{
			result[i] = str[i];
		}
	}
	result[length] = '\0';
	return result;
}

char *TRANSFORMATION_STR(char* str)
{
	int length = 0;
	while (str[length] != 0) length++;

	char* numbers = (char*)malloc((length + 1) * (sizeof(char)));
	char* letteres = (char*)malloc((length + 1) * (sizeof(char)));
	char* other = (char*)malloc((length + 1) * (sizeof(char)));
	int N_count = 0, T_count = 0, O_count = 0;

	for (int i = 0; i < length; i++)
	{
		if (isdigit(str[i]))
		{
			numbers[N_count++] = str[i];
		} 
		else if (isalpha(str[i]))
		{
			letteres[T_count++] = str[i];
		}
		else
		{
			other[O_count++] = str[i];
		}
	}

	numbers[N_count] = '\0';
	letteres[T_count] = '\0';
	other[O_count] = '\0';

	char* result = (char*)malloc((length + 1) * (sizeof(char)));
	sprintf(result, "%s%s%s", numbers, letteres, other);

	free(numbers);
	free(letteres);
	free(other);

	return result;
}

char* CONCATENATION_STR(int seed, char* strings[], int num_strings)
{
	srand(seed);
	char* result = (char*)malloc(sizeof(char));
	result[0] = '\0';

	int* used = (int*)malloc(num_strings * sizeof(int));
	for (int i = 0; i < num_strings; i++) used[i] = 0;

	int remaining = num_strings;
	while (remaining > 0)
	{
		int idx = rand() % num_strings;
		if (used[idx] == 0)
		{
			int old_length = strlen(result);

			int new_length = strlen(strings[idx]);

			char* new_result = (char*)malloc((old_length + new_length + 1) * sizeof(char));
			strcpy(new_result, result);
			strcat(new_result, strings[idx]);

			free(result);
			result = new_result;

			used[idx] = 1;
			remaining--;
		}
	}

	free(used);

	return result;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s [-l|-r|-u|-n|-c] string [seed [strings...]]\n", argv[0]);
		return NULL;
	}