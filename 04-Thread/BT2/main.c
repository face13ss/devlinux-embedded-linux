#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUMBER_THREADS 3
#define INCREMENT_PER_THREAD 100000

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;

static long int counter = 0;

void *increment_counter(void *arg) {
    pthread_mutex_lock(&lock1);
    for (size_t i = 0; i < INCREMENT_PER_THREAD; i++) {
        counter++;
    }
    pthread_mutex_unlock(&lock1);
    return NULL;
}



int main()
{
    pthread_t threads[NUMBER_THREADS];
    
    for(size_t i = 0; i <NUMBER_THREADS ; i++) {
        if(pthread_create(&threads[i], NULL, increment_counter, NULL) != 0 ) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (size_t i = 0; i < NUMBER_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }
    
    printf("Execected counter: %d\n", NUMBER_THREADS * INCREMENT_PER_THREAD);
    printf("Actual counter: %ld\n", counter);
    

    return 0;
}