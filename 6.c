#include <stdio.h>
#include <stdarg.h>

double polynomial_value(double x, int degree, ...) {
    va_list args;
    va_start(args, degree);

    double result = 0.0;

    for (int i = degree; i >= 0; i--) {
        double coefficient = va_arg(args, double);
        result = result * x + coefficient;
    }

    va_end(args);
    return result;
}

int main() {
    //  2x^3 + 3x^2 + 4x + 5 в точке x = 2
    double x = 2.0;
    int degree = 3;
    double value = polynomial_value(x, degree, 2.0, 3.0, 4.0, 5.0);
    printf("The value of the polynomial 2x^3 + 3x^2 + 4x + 5 в точке x = %.2f: %.2f\n", x, value);

    //  x^2 - 4x + 4 в точке x = 2
    x = 2.0;
    degree = 2;
    value = polynomial_value(x, degree, 1.0, -4.0, 4.0);
    printf("The value of the polynomial x^2 - 4x + 4 в точке x = %.2f: %.2f\n", x, value);

    // 5x^4 + 0x^3 + 0x^2 + 0x + 1 в точке x = 1
    x = 1.0;
    degree = 4;
    value = polynomial_value(x, degree, 5.0, 0.0, 0.0, 0.0, 1.0);
    printf("The value of the polynomial 5x^4 + 0x^3 + 0x^2 + 0x + 1 в точке x = %.2f: %.2f\n", x, value);

    return 0;
}