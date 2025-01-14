#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
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



int kaprekar(char const *number,int base, int *ans, ...) {

    int err, int_number, i, div, left, right;
    double square;
    size_t number_digits_count, square_digits_count;

    if (ans == NULL || number == NULL) {
        puts("Error ans or number");
        return 1;
    }
    if (base < 2 || base > 36) {
        puts("Error base");
        return 1;
    }

    int_number = convertToDecimal(number, base);
    if (int_number == -1) {
        return 1;
    }

   /* err = catoi(number, base, &int_number);
    if (err) {
        return err;
    }*/

    if (int_number == 1) {
        *ans = 1;
        return 0;
    }

    square = int_number * int_number;

    number_digits_count = strlen(number);
    square_digits_count = (size_t)log10(square) + 1;

    for (i = 1; i < square_digits_count; ++i) {
        div = (int)pow(base, i);

        left = ((int)square) / div;
        right = ((int)square) % div;

        if (left + right == int_number) {
            *ans = 1;
            return 0;
        }
    }
    *ans = 0;
    return 0;
}


int final(size_t count, size_t base, ...) {

    int i = 0;

    if (base < 2 || base > 36) {
        puts("Error base");
        return 1;
    }
    va_list args;
    va_start(args, base);

    char* ZXC;
    int ans;
    int err = 0; 

    for (i; i < count; i++) {

        ZXC = va_arg(args, char*);
        err = kaprekar(ZXC, base, &ans);

        if (err) {
            return err;
        }

        if (ans) {
            printf("%s\n", ZXC);
        }
    }
    return 0;
}

int main() {

    int result;


    result = final(3, 10, "45", "80", "1");

    return result;
}