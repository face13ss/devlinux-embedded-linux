#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THRESHOLD 10

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int counter = 0;

void *thread_handler(void *arg) {
    printf("start thread");
    
    // Producer
    pthread_mutex_lock(&lock);
    while (counter < THRESHOLD)
    {
        printf("Counter = %d\n", ++counter);
        sleep(1);
    }
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}



int main()
{
    int ret;
    pthread_t thread_id;

    if(ret = pthread_create(&thread_id, NULL, &thread_handler, NULL))
    {
        printf("pthread_create() error number %d", ret);
        return -1;
    }

    pthread_mutex_lock(&lock);
    while (1)
    {
        // pthread_cond_wait se unlock mutex
        pthread_cond_wait(&cond, &lock);
        printf("Global variable counter = %d.\n", counter);
        counter = 0;
        break;
    }
    pthread_mutex_unlock(&lock);
    
    pthread_join(thread_id, NULL);
    
    return 0;
}