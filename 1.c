#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* VMP( unsigned int num, int r)
{
	if ( r < 1 || r > 5) 
	{
		puts("Error");
		return NULL;
	}

	if ( num == NULL)
	{
		char* res = (char*)malloc(2);
		if (res == NULL) return NULL;
		strcpy(res, "\0");
		return res;
	}

	unsigned int base = 1U << r;

	int len = 0;
	unsigned int temp = num;

	while (temp > 0)
	{
		len++;
		temp >>= r;
	}
	
	char* result = (char*)malloc(len + 1);
	if (result == 0) return NULL;
	result[len] = '\0';

	char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = len -1; i>=0; i--)
	{
		unsigned int remainder = num & (base - 1);
		result[i] = digits[remainder];
		num >>= r;
	}
	return result;
}

int main()
{
	unsigned int num;
	int r;
	
	puts("Enter num:");
	scanf("%u", &num);

	puts("Enter r:");
	scanf("%d", &r);

	char* result = VMP(num, r);
	
	if (result)
	{
		printf("Final = %s\n", result);
		free(result);
	} 
	else
	{
		puts("Error");
	}

	return 0;
}