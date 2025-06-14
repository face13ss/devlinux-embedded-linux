#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {

    int status, retVal;
    pid_t pid = fork();
    if (pid < 0) {
        printf("Can't create child process\n");
    }
    else if ( pid == 0) {
        printf("child process, pid=%d\n",getpid());
        // while(1)
        //     ;
        return -1;
    }
    else 
    {
        retVal = wait(&status);
        if (WIFEXITED(status)){
            printf("true\n");
        }
        if (retVal == -1) {
            printf("wait() unsuccessfull\n");
        }
        printf("WIFEXITED: %d and WEXITSTATUS: %d\n", WIFEXITED(status), WEXITSTATUS(status));
        printf("child process status: %d and return value: %d\n", status, retVal);
    }

    return 0;
}