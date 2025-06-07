#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int second = 0;

void readSignal(int signal) {
    if (signal == SIGALRM){
        printf("Timer: %d seconds\n", ++second);
    }
    if (second == 10)
        exit(1);
    alarm(1);
}

int main() {
   signal(SIGALRM, readSignal);
   alarm(1);
   while (1);
   
    return 0;
}