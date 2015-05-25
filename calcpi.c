#include <stdio.h>

static long num_rects = 100000;

/*
 * pi = integral 0-1 4/(1+x^2) dx
 */
void main()
{
    int i;
    double mid, height, width, sum = 0.0;
    double area;

    width = 1.0/(double)num_rects;
    for (i = 0; i < num_rects; i++) {
        mid = (i + 0.5) * width;
        height = 4.0/(1.0 + mid*mid);
        sum += height;
    }

    area = width * sum;
    printf("Computed pi = %f\n", area);
}
