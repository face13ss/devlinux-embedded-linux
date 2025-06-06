#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t tid1, tid2;


static void *thr_handler1(void *args) {
    printf("Hi im thread %ld\n", tid1);
    sleep(5);
}

static void *thr_handler2(void *args) {
    printf("Hi im thread %ld\n", tid2);
    sleep(10);
}

int main(int argc, char const *argv[])
{
    int ret;

    if (ret = pthread_create(&tid1, NULL, &thr_handler1, NULL)){
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }
    if (ret = pthread_create(&tid2, NULL, &thr_handler2, NULL)){
        printf("pthread_create() error number=%d\n", ret);
        return -1;
    }

    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("join thread and end\n");

    return 0;
}