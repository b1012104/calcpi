#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 4

const long num_rects = 100000;
pthread_mutex_t mutex;
double area = 0.0;

/*
 * pi = integral 0-1 4/(1+x^2) dx
 */
void *threadFunction(void *pArg)
{
    int num = *((int *)pArg);
    int i;
    double partialHeight = 0.0, lWidth = 1.0 / num_rects, x;

    for (i = num; i < num_rects; i+= NUM_THREADS) {
        x = (i + 0.5) / num_rects;
        partialHeight += 4.0 / (1.0 + x*x);
    }

    pthread_mutex_lock(&mutex);
    area += partialHeight * lWidth;
    pthread_mutex_unlock(&mutex);
}

void main()
{
    pthread_t tid[NUM_THREADS];
    int tnum[NUM_THREADS];
    int i;

    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_THREADS; i++) {
        tnum[i] = i;
        pthread_create(&tid[i], NULL, threadFunction, (void *)&tnum[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Computed pi = %f\n", area);
}
