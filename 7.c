#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

#define INVALID_NUMBER 2
#define SIZE 6

int convertToDecimal(const char* str, int base) {
    if (base < 2 || base > 36) {
        fprintf(stderr, "Base must be in the range [2..36]\n");
        return -1;
    }

    int result = 0;
    int sign = 1;
    const char* ptr = str;

    if (*ptr == '-') {
        sign = -1;
        ptr++;
    }
    else if (*ptr == '+') {
        ptr++;
    }

    while (*ptr) {
        int value;

        if (isdigit(*ptr)) {
            value = *ptr - '0';
        }
        else if (isalpha(*ptr)) {
            value = tolower(*ptr) - 'a' + 10;
        }
        else {
            fprintf(stderr, "Invalid character '%c' for base %d\n", *ptr, base);
            return -1;
        }

        if (value >= base) {
            fprintf(stderr, "Character '%c' is not valid for base %d\n", *ptr, base);
            return -1;
        }

        if (result > (INT_MAX - value) / base) {
            fprintf(stderr, "Integer overflow occurred\n");
            return -1;
        }

        result = result * base + value;
        ptr++;
    }

    return result * sign;
}

int Kaprekar(const char* number, int base, int* ans) {
    if (ans == NULL || number == NULL) {
        return 1;
    }
    if (base < 2 || base > 36) {
        return 1;
    }

    int int_number = convertToDecimal(number, base);
    if (int_number == -1) {
        return 1;
    }

    if (int_number == 1) {
        *ans = 1;
        return 0;
    }

    double square = int_number * int_number;

    size_t number_digits_count = strlen(number);
    size_t square_digits_count = (size_t)log10(square) + 1;

    int i;
    for (i = 1; i < square_digits_count; ++i) {
        int div = (int)pow(base, i);

        int left = ((int)square) / div;
        int right = ((int)square) % div;

        if (left + right == int_number) {
            *ans = 1;
            return 0;
        }
    }

    *ans = 0;
    return 0;
}

int final(size_t count, size_t base, ...) {
    if (base < 2 || base > 36) {
        return 1;
    }

    va_list args;
    va_start(args, base);

    int i;
    int err = 0;

    for (i = 0; i < count; i++) {
        char* ZXC = va_arg(args, char*);
        int ans;
        err = Kaprekar(ZXC, base, &ans);

        if (err) {
            va_end(args);
            return err;
        }

        if (ans) {
            *(int*)va_arg(args, int*) = 1;
        }
        else {
            *(int*)va_arg(args, int*) = 0;
        }
    }

    va_end(args);
    return 0;
}

int main() {
    int result1, result2, result3;
    int err = final(3, 10, "45", &result1, "80", &result2, "1", &result3);

    if (err) {
        printf("Error occurred in final function\n");
        return err;
    }

    if (result1) {
        printf("45 is a Kaprekar number\n");
    }
    else {
        printf("45 is not a Kaprekar number\n");
    }

    if (result2) {
        printf("80 is a Kaprekar number\n");
    }
    else {
        printf("80 is not a Kaprekar number\n");
    }

    if (result3) {
        printf("1 is a Kaprekar number\n");
    }
    else {
        printf("1 is not a Kaprekar number\n");
    }

    return 0;
}