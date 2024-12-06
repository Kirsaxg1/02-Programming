#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define OK 0
#define INVALID_PARAMETERS -1
#define MEMORY_ALLOCATION_ERROR -2

#define POINTS_COUNT 3



typedef struct {
    double x;
    double y;
} Point;

int is_convex(int count, ...);

int main() {
    int count = 0;
    int result = 0;
    Point poins[POINTS_COUNT] = { {3, 5},{56, 7},{35, 58} };


    if (result == 1) {
        printf("vipukliy\n");
    }
    else if (result == 0) {
        printf("nevipukli\n");
    }
    else if (result == INVALID_PARAMETERS) {
        printf("nekorect parametri mnogougolnika\n");
    }
    else if (result == MEMORY_ALLOCATION_ERROR) {
        printf("error videleniya pamyati\n");
    }

    return OK;
}

int is_convex(int count, ...) {
    if (count < 3) return INVALID_PARAMETERS;

    va_list args;
    va_start(args, count);

    Point* points = (Point*)malloc(count * sizeof(Point));
    if (points == NULL) return MEMORY_ALLOCATION_ERROR;

    for (int i = 0; i < count; i++) {
        points[i].x = va_arg(args, double);
        points[i].y = va_arg(args, double);
    }
    va_end(args);

    double orientation = 0;
    double det;
    double epsilon = 1e-9;

    for (int i = 0; i < count; i++) {
        det = (points[(i + 1) % count].x - points[i].x) * (points[(i + 2) % count].y - points[i].y) -
            (points[(i + 1) % count].y - points[i].y) * (points[(i + 2) % count].x - points[i].x);

        if (fabs(det) > epsilon) {
            if (orientation == 0) orientation = det > 0 ? 1 : -1;
            else if ((det > 0 && orientation < 0) || (det < 0 && orientation > 0)) {
                free(points);
                return 0;
            }
        }
    }

    free(points);
    return 1;
}