//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//
//// Функция для поиска подстроки в файле без использования strlen
//void search_substring_in_files(const char* substring, int num_files, ...) {
//
//    va_list args;
//    va_start(args, num_files);
//
//    for (int i = 0; i < num_files; i++) {
//        char* filename = va_arg(args, char*);
//        FILE* file = fopen(filename, "r");
//
//        if (file == NULL) {
//            fprintf(stderr, "Ошибка открытия файла: %s\n", filename);
//            continue;
//        }
//
//        int line_num = 1;
//        char line[1024]; // Размер буфера для строки
//        int char_index = 1;
//        int substring_len = 0;
//        const char* p = substring;
//        while (*p != '\0') {
//            substring_len++;
//            p++;
//        }
//
//        while (fgets(line, sizeof(line), file) != NULL) {
//            int line_len = 0;
//            char* q = line;
//            while (*q != '\0' && *q != '\n') {
//                line_len++;
//                q++;
//            }
//
//            int found = 0;
//            for (int j = 0; j <= line_len - substring_len; ++j) {
//                int k = 0;
//                while (k < substring_len && line[j + k] == substring[k]) {
//                    k++;
//                }
//                if (k == substring_len) {
//                    printf("Файл: %s, строка: %d, позиция: %d\n", filename, line_num, char_index + j);
//                    found = 1;
//                }
//            }
//            if (found) {
//                char_index += line_len + 1; // +1 учитывает символ перевода строки '\n'
//            }
//            line_num++;
//            char_index = 1;
//
//        }
//
//        fclose(file);
//    }
//    va_end(args);
//}
//
//int main() {
//    // Пример использования функции
//    char* substring = "test"; // Пример подстроки
//    search_substring_in_files(substring, 2, "file1.txt", "file2.txt");
//
//    //Пример с пустой подстрокой.
//    char* empty_substring = "";
//    search_substring_in_files(empty_substring, 1, "file1.txt");
//
//    return 0;
//}