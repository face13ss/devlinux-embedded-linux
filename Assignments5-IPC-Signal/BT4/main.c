#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



void readSignal(int signal) {
    if (signal == SIGTSTP ){
        printf("SIGTSTP ignored\n");
    }
}

int main() {

   signal(SIGTSTP, readSignal);
   while (1)
   {
        printf("Process is running\n");
        sleep(1);
   }
   
    return 0;
}