#include <stdio.h>
#include <omp.h>

#define THREADS_NUM 4

static long num_rects = 100000;
void main()
{
    int i;
    double mid, height, width, sum = 0.0;
    double area;

    width = 1.0/(double)num_rects;

    omp_set_num_threads(THREADS_NUM);
#pragma omp parallel for private(mid, height) reduction(+:sum)
    for (i = 0; i < num_rects; i++) {
        mid = (i + 0.5) * width;
        height = 4.0/(1.0 + mid*mid);
        sum += height;
    }

    area = width * sum;
    printf("Computed pi = %f\n", area);
}
