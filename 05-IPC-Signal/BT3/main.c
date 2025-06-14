#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>


static int received = 0;

void readUsual(int signal) {
    if (signal == SIGUSR1){
        printf("Received signal from parent\n");
        received++;
    }
}

int main() {

    int status, retVal;
    signal(SIGUSR1, readUsual);
    pid_t pid = fork();
    if (pid < 0) {
        printf("Can't create child process\n");
    }
    else if ( pid == 0) {
        while (received < 5)
            ;
            return -1;
    }
    else 
    {
        for (size_t i = 0; i < 5; i++)
        {
            kill(pid,SIGUSR1);
        }
        
        retVal = wait(&status);
        if (retVal == -1) {
            printf("wait() unsuccessfull\n");
        }
        printf("child process status: %d and return value: %d\n", status, retVal);
    }

    return 0;
}