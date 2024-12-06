//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//
//int return_resources(int flag, ...);
//
//#define INVALID_FLAG -1
//
//int main( int argc, char* argv[]){
//
//	int err;
//	char* str = (char*)malloc(50 * sizeof(char));
//	char* arr = (char*)malloc(50 * sizeof(char));
//
//	FILE* ptr = fopen("sos.txt", "w");
//
//	printf("\naddress of variables: %p, %p, %p\n", str, arr, ptr);
//	err = return_resources('f', str, 'c', ptr, 'f', arr, 'w', str, 'f', NULL);
//
//	if (err != 0) {
//		puts("Vse fignya peredelivai :(");
//		return err;
//	}
//	return 0;
//}
//
//int return_resources(int flag, ...) {
//
//	int c = flag;
//	void* arg;
//	va_list listik;
//	va_start(listik, flag);
//
//	while (1) {
//
//		arg = va_arg(va_list, void*);
//		if (arg == NULL) return 0;
//
//		if (c == 'f')
//		{
//			printf("freeing memory at %p\n", arg);
//			free(arg);
//		} else if( c =='c'){
//			printf("closing file var at %p\n", arg);
//			fclose((FILE*)arg);
//		}
//		else { 
//			printf("uehalo vse GG VP %c\n", c);
//			return INVALID_FLAG;
//		}
//		c = va_arg(va_list, int);
//	}
//	va_end(listik);
//	return 0;
//}