#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

static int received = 0;

void readSignal(int signal) {
    if (signal == SIGINT){
        printf("Number of SIGINT received: %d\n", ++received);
    }
    if (received == 3){
        exit(0);
    }
}

int main() {

   signal(SIGINT, readSignal);
   while (1)
   {
        printf("Process is running\n");
        sleep(1);
   }
   
    return 0;
}