#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

static int num_even = 0, num_odd = 0;
int numbers[ARRAY_SIZE] = {0};

void * even_counter(void *arg) {
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        if (numbers[i] % 2 == 0) {
            num_even++;
        }
    }
    
}

void * odd_counter(void *arg) {
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        if (numbers[i] % 2 != 0) {
            num_odd++;
        }
    }
    
}



int main()
{
    int ret;
    pthread_t thread_id_1, thread_id_2;

    srand(time(NULL));
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        numbers[i] = rand() % 100 + 1;
        printf("Random number: %d\n", numbers[i]);
    }

    if(ret = pthread_create(&thread_id_1, NULL, &even_counter, NULL))
    {
        printf("pthread_create() error number %d", ret);
        return -1;
    }

    if(ret = pthread_create(&thread_id_2, NULL, &odd_counter, NULL))
    {
        printf("pthread_create() error number %d", ret);
        return -1;
    }

    pthread_join(thread_id_1, NULL);
    pthread_join(thread_id_2, NULL);

    printf("Numbers of even number: %d\n", num_even);
    printf("Numbers of odd number: %d\n", num_odd);
    

    return 0;
    // int ret;
    // pthread_t thread_id;

    // if(ret = pthread_create(&thread_id, NULL, &thread_handler, NULL))
    // {
    //     printf("pthread_create() error number %d", ret);
    //     return -1;
    // }

    // pthread_mutex_lock(&lock);
    // while (1)
    // {
    //     // pthread_cond_wait se unlock mutex
    //     pthread_cond_wait(&cond, &lock);
    //     printf("Global variable counter = %d.\n", counter);
    //     counter = 0;
    //     break;
    // }
    // pthread_mutex_unlock(&lock);
    
    // pthread_join(thread_id, NULL);
    
    // return 0;
}