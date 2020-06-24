#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int sum = 0;
pthread_mutex_t pm;

void* add_half(const int* end)
{
    pthread_mutex_lock(&pm);
    for(int i = (*end)/2 + 1; i <= (*end); ++i)
        sum += i;
    pthread_mutex_unlock(&pm);
}

int main(int argc, char* argv[])
{
    int end = atoi(argv[1]);
//    int end = 100;
    pthread_t pt;
    pthread_mutex_init(&pm, NULL);

    pthread_create(&pt, NULL, (void *)add_half, &end);
    pthread_mutex_lock(&pm);
    for(int i = 0; i <= end/2; i++)
        sum += i;
    pthread_mutex_unlock(&pm);
    pthread_join(pt, NULL);
    printf("%d\n", sum);
    return 0;
}