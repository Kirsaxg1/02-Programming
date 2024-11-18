//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//char* VMP(int num, int base) 
//{
//	if (base < 2 || base > 32)
//	{
//		puts("Error");
//		return NULL;
//	}
//	
//	char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
//	char buffer[100];
//	int index = 0;
//
//	if (num == 0 )
//	{
//		buffer[index++] = '0';
//	} else 
//	{
//		while (num > 0)
//		{
//			int remainder = num % base;
//			buffer[index++] = digits[remainder];
//			num /= base;
//		}
//	}
//
//	buffer[index] = '\0';
//
//	int left = 0, right = index - 1;
//
//	while (left < right)
//	{
//		char temp = buffer[left];
//		buffer[left] = buffer[right];
//		buffer[right] = temp;
//		left++;
//		right--;
//	}
//
//	char* result = (char*)malloc(index + 1);
//	if (result == NULL)
//	{
//		puts("Error");
//		return NULL;
//	}
//	strcpy(result, buffer);
//	return result;
//}
//
//int main()
//{
//	int num, base;
//	puts("Enter an num");
//	scanf("%d", &num);
//	puts("Enter an base 2 - 32");
//	scanf("%d", &base);
//
//	char* result = VMP(num, base);
//	if (result != NULL)
//	{
//		printf("Result: %s\n", result);
//		free(result);
//	}
//	return 0;
//}