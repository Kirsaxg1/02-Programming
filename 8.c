//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdarg.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//int sum_in_base(int base, size_t number_count, char** ans, ...);
//int final_sum(char** ans, int base,const char * num_1, const char* num_2);
//
//int char_to_int(char num, int *num2) {
//
//
//
//	if (num2 == NULL) {
//		return 1;
//	} 
//
//	//if (!isalnum(num2)) {
//	//	return 1;
//	//}
//
//	if (isdigit(num)) {
//		*num2 = num - '0';
//	}
//	else if (isalpha(num)) {
//		*num2 = num - 'A' + 10;
//	}
//	else {
//		return 1;
//	}
//	return 0;
//}
//
//int int_to_char(int num, char* num2) {
//
//	if (num2 == NULL) {
//		return 1;
//	}
//	if (num < 0 || num > 35) {
//		return 1;
//	}
//	if (num < 10) {
//		*num2 = num + '0';
//	} else{
//		*num2 = num + 'A' - 10;
//	}
//	return 0;
//}
//
//
//
//
//
//int sum_in_base(int base, size_t number_count, char** ans, ...) {
//
//	int i, err;
//
//	char* num = NULL, *temp = NULL;
//
//	va_list args;
//
//	if (ans == NULL) {
//		return 1;
//	}
//
//	if (base < 2 || base > 36) {
//		puts("Error base");
//		return 1;
//	}
//
//	va_start(args, ans);
//
//
//	if (number_count == 1) {
//		num = va_arg(args, char*);
//		*ans = (char*)malloc((strlen(num) + 1) * sizeof(char));
//
//		if (*ans == NULL) {
//			puts("error memory");
//			return 1;
//		}
//		strcpy(*ans, num);
//		va_end(args);
//		return 0;
//	}
//
//	num = va_arg(args, char*);
//	temp = va_arg(args, char*);
//	printf("Sum %s and %s\n", num, temp);
//	err = final_sum(ans, base, num, temp);
//
//	if (err) {
//		va_end(args);
//		return err;
//	}
//
//
//	for (i = 2; i < number_count; i++) {
//		num = va_arg(args, char*);
//		printf("sum %s and %s\n", *ans, num);
//		err = final_sum(ans, base, *ans, num);
//		if (err) {
//			free(*ans);
//			*ans = NULL;
//			va_end(args);
//			return err;
//		}
//	}
//	va_end(args);
//	return 0;
//}
//
//int final_sum(char** ans, int base, char const* num_1, char const* num_2) {
//
//	int i, j, k, carry = 0, digit_1, digit_2, err, sum;
//	size_t len_1, len_2, max_len;
//
//	char* temp_num, c;
//
//	len_1 = strlen(num_1);
//	len_2 = strlen(num_2);
//	max_len = (len_1 > len_2) ? len_1 : len_2;
//
//	temp_num = (char*)calloc((max_len + 2), sizeof(char));
//
//	if (temp_num == NULL) {
//		puts("Error memory");
//		return 1;
//	}
//
//	temp_num[max_len + 1] = '\0';
//
//	i = len_1 - 1;
//	j = len_2 - 1;
//	k = max_len;
//
//	////
//
//	while (i >= 0 || j >= 0 || carry) {
//		if (i >= 0) {
//			err = char_to_int(num_1[i--], &digit_1);
//			if (err) {
//				free(temp_num);
//				return err;
//			}
//		}
//		else {
//			digit_1 = 0;
//		}
//		if (j >= 0) {
//			err = char_to_int(num_2[j--], &digit_2);
//			if (err) {
//				free(temp_num);
//				return err;
//			}
//		}
//		else {
//			digit_2 = 0;
//		}
//		sum = digit_1 + digit_2 + carry;
//		carry = sum / base;
//
//		err = int_to_char(sum % base, &c);
//		printf("%c\n", c);
//		temp_num[k--] = c;
//		if (err) {
//			free(temp_num);
//			return err;
//		}
//	}
//	if (carry) {
//		temp_num[0] = '1';
//	}
//		else {
//			memmove(temp_num, temp_num + 1, max_len + 1);
//		}
//		free(*ans);
//		*ans = temp_num;
//		return 0;
//	}
//
//
//int main() {
//	int err;
//	char* sum = NULL;
//
//	int const base = 16;
//	err = sum_in_base(base, 5, &sum,"5", "ABCDEF", "52", "AF5E", "FE52");
//	printf("sum in base %d: %s\n", base, sum);
//	free(sum);
//	return err;
//}