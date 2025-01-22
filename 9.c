#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int str_to_int(const char* str, int base) {
    if (str == NULL || base < 2 || base > 36) {
        return 0;
    }

    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; i++) {
        char c = str[i];
        int digit;

        if (isdigit(c)) {
            digit = c - '0';
        }
        else if (isalpha(c)) {
            digit = toupper(c) - 'A' + 10;
        }
        else {
            return 0;
        }

        if (digit >= base) {
            return 0;
        }

        result = result * base + digit;
    }

    return result * sign;
}

void int_to_roman(int num, char* result) {
    if (result == NULL) {
        return;
    }

    int val[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    char* syms[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    result[0] = '\0';

    int i;
    for (i = 0; i < 13; i++) {
        while (num >= val[i]) {
            strcat(result, syms[i]);
            num -= val[i];
        }
    }
}

void int_to_zeckendorf(unsigned int num, char* result) {
    if (result == NULL) {
        return;
    }

    if (num == 0) {
        strcpy(result, "0");
        return;
    }

    int fib[46];
    fib[0] = 1;
    fib[1] = 2;

    int i;
    for (i = 2; i < 46; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    int idx = 45;
    while (fib[idx] > num) idx--;

    result[0] = '\0';
    for (; idx >= 0; idx--) {
        if (num >= fib[idx]) {
            strcat(result, "1");
            num -= fib[idx];
        }
        else {
            strcat(result, "0");
        }
    }
    strcat(result, "1");
}

void int_to_base(int num, int base, char* result, int uppercase) {
    if (result == NULL || base < 2 || base > 36) {
        return;
    }

    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (uppercase) {
        digits[10] = 'A';
    }

    int i = 0;
    int is_negative = 0;

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    do {
        result[i++] = digits[num % base];
        num /= base;
    } while (num > 0);

    if (is_negative) {
        result[i++] = '-';
    }
    result[i] = '\0';

    int j;
    for (j = 0; j < i / 2; j++) {
        char temp = result[j];
        result[j] = result[i - j - 1];
        result[i - j - 1] = temp;
    }
}

void print_memory_dump(const void* ptr, size_t size, char* result) {
    if (result == NULL || ptr == NULL) {
        return;
    }

    const unsigned char* bytes = (const unsigned char*)ptr;
    result[0] = '\0';

    size_t i;
    for (i = 0; i < size; i++) {
        char byte_str[9];
        int j;
        for (j = 7; j >= 0; j--) {
            byte_str[7 - j] = (bytes[i] & (1 << j)) ? '1' : '0';
        }
        byte_str[8] = '\0';
        strcat(result, byte_str);
        if (i < size - 1) {
            strcat(result, " ");
        }
    }
}

int overprintf(const char* format, ...) {
    if (format == NULL) {
        return -1;
    }

    va_list args;
    va_start(args, format);
    int count = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'R' && *(format + 1) == 'o') {
                format += 2;
                int num = va_arg(args, int);
                char roman[20] = { 0 };
                int_to_roman(num, roman);
                count += printf("%s", roman);
            }
            else if (*format == 'Z' && *(format + 1) == 'r') {
                format += 2;
                unsigned int num = va_arg(args, unsigned int);
                char zeck[100] = { 0 };
                int_to_zeckendorf(num, zeck);
                count += printf("%s", zeck);
            }
            else if (*format == 'C' && *(format + 1) == 'v') {
                format += 2;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                char base_str[100] = { 0 };
                int_to_base(num, base, base_str, 0);
                count += printf("%s", base_str);
            }
            else if (*format == 'C' && *(format + 1) == 'V') {
                format += 2;
                int num = va_arg(args, int);
                int base = va_arg(args, int);
                char base_str[100] = { 0 };
                int_to_base(num, base, base_str, 1);
                count += printf("%s", base_str);
            }
            else if (*format == 't' && *(format + 1) == 'o') {
                format += 2;
                char* str = va_arg(args, char*);
                int base = va_arg(args, int);
                int num = str_to_int(str, base);
                count += printf("%d", num);
            }
            else if (*format == 'T' && *(format + 1) == 'O') {
                format += 2;
                char* str = va_arg(args, char*);
                int base = va_arg(args, int);
                int num = str_to_int(str, base);
                count += printf("%d", num);
            }
            else if (*format == 'm' && *(format + 1) == 'i') {
                format += 2;
                int num = va_arg(args, int);
                char dump[100] = { 0 };
                print_memory_dump(&num, sizeof(num), dump);
                count += printf("%s", dump);
            }
            else if (*format == 'm' && *(format + 1) == 'u') {
                format += 2;
                unsigned int num = va_arg(args, unsigned int);
                char dump[100] = { 0 };
                print_memory_dump(&num, sizeof(num), dump);
                count += printf("%s", dump);
            }
            else if (*format == 'm' && *(format + 1) == 'd') {
                format += 2;
                double num = va_arg(args, double);
                char dump[100] = { 0 };
                print_memory_dump(&num, sizeof(num), dump);
                count += printf("%s", dump);
            }
            else if (*format == 'm' && *(format + 1) == 'f') {
                format += 2;
                float num = va_arg(args, double);
                char dump[100] = { 0 };
                print_memory_dump(&num, sizeof(num), dump);
                count += printf("%s", dump);
            }
            else {
                putchar('%');
                putchar(*format);
                count += 2;
                format++;
            }
        }
        else {
            putchar(*format);
            count++;
            format++;
        }
    }

    va_end(args);
    return count;
}

int main() {
    overprintf("Roman: %Ro\n", 2023);
    overprintf("Zeckendorf: %Zr\n", 123);
    overprintf("Base 16: %Cv\n", 255, 16);
    overprintf("Base 16 (uppercase): %CV\n", 255, 16);
    overprintf("String to int: %to\n", "ff", 16);
    overprintf("String to int (uppercase): %TO\n", "FF", 16);
    overprintf("Memory dump (int): %mi\n", 123);
    overprintf("Memory dump (unsigned int): %mu\n", 123);
    overprintf("Memory dump (double): %md\n", 123.456);
    overprintf("Memory dump (float): %mf\n", 123.456f);

    return 0;
}