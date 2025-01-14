#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

double the_value_of_the_polynomial(double x, int n, ...) {

	va_list args;
	va_start(args, n);

	double result = 0.0;
	double ratio;

	for (int i = 0; i <= n; i++) {

		ratio = va_arg(args, double);
		result += ratio * pow(x, n - i);
	}
	va_end(args);
	return result; 
}

int main() {

	// 3x³ + 2x² - 5x + 1 in point x = 2
	double x = 2.0;
	int n = 3;

	double result = the_value_of_the_polynomial(x, n, 3.0, 2.0, -5.0, 1.0);
	printf("\n result = %.1f: %.1f\n", x, result);
	return 0;
}
