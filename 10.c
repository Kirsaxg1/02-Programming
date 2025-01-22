#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int roman_to_int(const char* str) {
    if (str == NULL) {
        return 0;
    }

    int val[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
    const char* syms[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };
    int num = 0;
    int i = 0;

    while (*str) {
        if (strncmp(str, syms[i], strlen(syms[i])) == 0) {
            num += val[i];
            str += strlen(syms[i]);
        }
        else {
            i++;
        }
    }
    return num;
}

unsigned int zeckendorf_to_int(const char* str) {
    if (str == NULL) {
        return 0;
    }

    if (strcmp(str, "0") == 0) return 0;

    int fib[46];
    fib[0] = 1;
    fib[1] = 2;

    int i;
    for (i = 2; i < 46; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    unsigned int num = 0;
    int len = strlen(str);

    for (i = 0; i < len - 1; i++) {
        if (str[i] == '1') {
            num += fib[len - i - 2];
        }
    }
    return num;
}

int str_to_int_base(const char* str, int base) {
    if (str == NULL || base < 2 || base > 36) {
        return 0;
    }
    return (int)strtol(str, NULL, base);
}

int overscanf(const char* format, ...) {
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
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                char buffer[100] = { 0 };
                if (scanf("%99s", buffer) == 1) {
                    *num = roman_to_int(buffer);
                    count++;
                }
            }
            else if (*format == 'Z' && *(format + 1) == 'r') {
                format += 2;
                unsigned int* num = va_arg(args, unsigned int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                char buffer[100] = { 0 };
                if (scanf("%99s", buffer) == 1) {
                    *num = zeckendorf_to_int(buffer);
                    count++;
                }
            }
            else if (*format == 'C' && *(format + 1) == 'v') {
                format += 2;
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                int base = va_arg(args, int);
                char buffer[100] = { 0 };
                if (scanf("%99s", buffer) == 1) {
                    *num = str_to_int_base(buffer, base);
                    count++;
                }
            }
            else if (*format == 'C' && *(format + 1) == 'V') {
                format += 2;
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                int base = va_arg(args, int);
                char buffer[100] = { 0 };
                if (scanf("%99s", buffer) == 1) {
                    *num = str_to_int_base(buffer, base);
                    count++;
                }
            }
            else {
                format++;
            }
        }
        else {
            format++;
        }
    }

    va_end(args);
    return count;
}

int overfscanf(FILE* stream, const char* format, ...) {
    if (stream == NULL || format == NULL) {
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
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                char buffer[100] = { 0 };
                if (fscanf(stream, "%99s", buffer) == 1) {
                    *num = roman_to_int(buffer);
                    count++;
                }
            }
            else if (*format == 'Z' && *(format + 1) == 'r') {
                format += 2;
                unsigned int* num = va_arg(args, unsigned int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                char buffer[100] = { 0 };
                if (fscanf(stream, "%99s", buffer) == 1) {
                    *num = zeckendorf_to_int(buffer);
                    count++;
                }
            }
            else if (*format == 'C' && *(format + 1) == 'v') {
                format += 2;
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                int base = va_arg(args, int);
                char buffer[100] = { 0 };
                if (fscanf(stream, "%99s", buffer) == 1) {
                    *num = str_to_int_base(buffer, base);
                    count++;
                }
            }
            else if (*format == 'C' && *(format + 1) == 'V') {
                format += 2;
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                int base = va_arg(args, int);
                char buffer[100] = { 0 };
                if (fscanf(stream, "%99s", buffer) == 1) {
                    *num = str_to_int_base(buffer, base);
                    count++;
                }
            }
            else {
                format++;
            }
        }
        else {
            format++;
        }
    }

    va_end(args);
    return count;
}

int oversscanf(const char* str, const char* format, ...) {
    if (str == NULL || format == NULL) {
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
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                char buffer[100] = { 0 };
                if (sscanf(str, "%99s", buffer) == 1) {
                    *num = roman_to_int(buffer);
                    count++;
                }
            }
            else if (*format == 'Z' && *(format + 1) == 'r') {
                format += 2;
                unsigned int* num = va_arg(args, unsigned int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                char buffer[100] = { 0 };
                if (sscanf(str, "%99s", buffer) == 1) {
                    *num = zeckendorf_to_int(buffer);
                    count++;
                }
            }
            else if (*format == 'C' && *(format + 1) == 'v') {
                format += 2;
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                int base = va_arg(args, int);
                char buffer[100] = { 0 };
                if (sscanf(str, "%99s", buffer) == 1) {
                    *num = str_to_int_base(buffer, base);
                    count++;
                }
            }
            else if (*format == 'C' && *(format + 1) == 'V') {
                format += 2;
                int* num = va_arg(args, int*);
                if (num == NULL) {
                    va_end(args);
                    return -1;
                }
                int base = va_arg(args, int);
                char buffer[100] = { 0 };
                if (sscanf(str, "%99s", buffer) == 1) {
                    *num = str_to_int_base(buffer, base);
                    count++;
                }
            }
            else {
                format++;
            }
        }
        else {
            format++;
        }
    }

    va_end(args);
    return count;
}

int main() {
    int num1;
    unsigned int num2;
    int num3;
    int num4;

    printf("Enter a Roman numeral: ");
    overscanf("%Ro", &num1);
    printf("You entered: %d\n", num1);

    printf("Enter a Zeckendorf representation: ");
    overscanf("%Zr", &num2);
    printf("You entered: %u\n", num2);

    printf("Enter a number in base 16 (lowercase): ");
    overscanf("%Cv", &num3, 16);
    printf("You entered: %d\n", num3);

    printf("Enter a number in base 16 (uppercase): ");
    overscanf("%CV", &num4, 16);
    printf("You entered: %d\n", num4);

    FILE* file = fopen("C:\\Users\\GIGABYTE\\Desktop\\test1.txt", "r");
    if (file) {
        int num5;
        unsigned int num6;
        int num7;
        int num8;

        overfscanf(file, "%Ro", &num5);
        printf("Read from file: %d\n", num5);

        overfscanf(file, "%Zr", &num6);
        printf("Read from file: %u\n", num6);

        overfscanf(file, "%Cv", &num7, 16);
        printf("Read from file: %d\n", num7);

        overfscanf(file, "%CV", &num8, 16);
        printf("Read from file: %d\n", num8);

        fclose(file);
    }
    else {
        printf("Failed to open file.\n");
    }

    const char* input = "MMXXIII 10101011 ff FF";
    int num9;
    unsigned int num10;
    int num11;
    int num12;

    oversscanf(input, "%Ro %Zr %Cv %CV", &num9, &num10, &num11, 16, &num12, 16);
    printf("Result of oversscanf: %d %u %d %d\n", num9, num10, num11, num12);

    return 0;
}