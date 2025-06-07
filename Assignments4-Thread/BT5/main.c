#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define NUMBER_READ_THREAD 5
#define NUMBER_WRITE_THREAD 2

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;


int data = {0};

void *read_data(void *arg) {
    while (1)
    {
    pthread_rwlock_rdlock(&rwlock);
    printf("Reader thread %ld is reading data: %d\n", (long)arg, data);
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
    }
    
    return NULL;
}

void *write_data(void *arg) {
    while (1)
    {
    pthread_rwlock_wrlock(&rwlock);
    printf("Writer thread %ld is writing data: %d\n",(long)arg,  ++data);
    pthread_rwlock_unlock(&rwlock);
    sleep(2);
    }
    
    return NULL;
}



int main()
{
    pthread_t threads_read[NUMBER_READ_THREAD];
    pthread_t threads_write[NUMBER_WRITE_THREAD];

    for(size_t i = 0; i <NUMBER_READ_THREAD ; i++) {
        if(pthread_create(&threads_read[i], NULL, read_data, (void*)(i+1)) != 0 ) {
            perror("Failed to create thread");
            return 1;
        }
    }
    for(size_t i = 0; i <NUMBER_WRITE_THREAD ; i++) {
        if(pthread_create(&threads_write[i], NULL, write_data, (void*)(i+1)) != 0 ) {
            perror("Failed to create thread");
            return 1;
        }
    }
    

    for (size_t i = 0; i < NUMBER_READ_THREAD; i++) {
        if (pthread_join(threads_read[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    for (size_t i = 0; i < NUMBER_WRITE_THREAD; i++) {
        if (pthread_join(threads_write[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}