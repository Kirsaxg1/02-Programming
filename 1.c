#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int nulik(unsigned int num)
{
    return (num == 0);
}

unsigned int add(unsigned int a, unsigned int b)
{
    unsigned int carry;
    while (!nulik(b)) {
        carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

int length_result(unsigned int num, int r)
{
    int len = 0;

    while (!nulik(num))
    {
        len = add(len, 1);
        num = num >> r;
    }
    return len;
}

char* decimal_to_base(unsigned int num, int r)
{
    if (r < 1 || r > 5)
    {
        return NULL;
    }

    if (nulik(num))
    {
        char* res = (char*)malloc(2);
        if (res == NULL) return NULL;
        strcpy(res, "0");
        return res;
        free(res);
    }

    unsigned int base = 1U << r;

    int len = length_result(num, r);

    char* result = (char*)malloc(add(len, 1));
    if (result == NULL) return NULL;
    result[len] = '\0';

    const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int i;
    unsigned int remainder;

    for (i = len - 1; i >= 0; i = add(i, -1))
    {
        remainder = num & (base - 1);
        result[i] = digits[remainder];
        num = num >> r;
    }

    return result;
}

int main()
{
    unsigned int num;
    int r;

    puts("Enter num:");

    if (scanf("%u", &num) != 1)
    {
        fprintf(stderr, "Invalid input for num\n");
        return 1;
    }

    puts("Enter r (1 to 5):");
    if (scanf("%d", &r) != 1)
    {
        fprintf(stderr, "Invalid input for r\n");
        return 1;
    }

    if (r < 1 || r > 5)
    {
        fprintf(stderr, "Error: r must be between 1 and 5\n");
        return 1;
    }

    char* result = decimal_to_base(num, r);

    if (result)
    {
        printf("Result in base 2^%d: %s\n", r, result);
        free(result);
    }
    else {
        fprintf(stderr, "Error: Memory allocation failed\n");
    }

    return 0;
}