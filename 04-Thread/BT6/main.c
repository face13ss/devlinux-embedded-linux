#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define NUMBER_THREADS 4
#define ARRAY_SIZE 1000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int numbers[ARRAY_SIZE] = {0};

long total = 0;

typedef struct {
    int *data;
    size_t size;
} split_array_t;

void *read_data(void *arg) {
    long sum = 0;
    split_array_t *args = (split_array_t *) arg;
    for (size_t i = 0; i < args->size; i++)
    {
        sum += args->data[i];
    }
    pthread_mutex_lock(&mutex);
    total += sum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main()
{
    pthread_t threads[NUMBER_THREADS];
    split_array_t arrays[NUMBER_THREADS];
    // init array
    srand(time(NULL));
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        numbers[i] = rand() % 100 + 1;
    }
    // Slip array

    int chunk_size = ARRAY_SIZE / NUMBER_THREADS;
    // Create thread
    for(size_t i = 0; i <NUMBER_THREADS ; i++) {
         arrays[i].data =numbers + i * chunk_size;
         arrays[i].size = (i == NUMBER_THREADS - 1) ? (ARRAY_SIZE - i * chunk_size) : chunk_size;
        if(pthread_create(&threads[i], NULL, read_data, &arrays[i]) != 0 ) {
            perror("Failed to create thread");
            return 1;
        }
    }

    
    // Join thread
    for (size_t i = 0; i < NUMBER_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    printf("Total of array with 1000000 element: %ld\n", total);

    return 0;
}