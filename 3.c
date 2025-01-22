#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int return_resources(int flag, ...);

#define INVALID_FLAG -1

int main(int argc, char* argv[]) {
    int err;
    char* str = (char*)malloc(50 * sizeof(char));
    char* arr = (char*)malloc(50 * sizeof(char));

    snprintf(str, 50, "This is a test string.");
    snprintf(arr, 50, "Another string.");

    FILE* ptr = fopen("C:\\Users\\GIGABYTE\\Desktop\\sos.txt", "w");
    if (ptr == NULL) {
        printf("Failed to open file 'sos.txt'. Check permissions or path.\n");
        free(str);
        free(arr);
        return 1;
    }

    fprintf(ptr, "String 1: %s\n", str);
    fprintf(ptr, "String 2: %s\n", arr);

    printf("\naddress of variables: %p, %p, %p\n", (void*)str, (void*)arr, (void*)ptr);

    err = return_resources('f', str, 'c', ptr, 'f', arr, 'w', str, 'f', NULL);

    if (err != 0) {
        puts("Vse fignya peredelivai :(");
        return err;
    }
    return 0;
}

int return_resources(int flag, ...) {
    int c = flag;
    void* arg;
    va_list listik;
    va_start(listik, flag);

    while (1) {
        arg = va_arg(listik, void*);
        if (arg == NULL) {
            va_end(listik);
            return 0;
        }

        if (c == 'f') {
            free(arg);
        }
        else if (c == 'c') {
            fclose((FILE*)arg);
        }
        else {
            va_end(listik);
            return INVALID_FLAG;
        }

        c = va_arg(listik, int);
    }

    va_end(listik);
    return 0;
}