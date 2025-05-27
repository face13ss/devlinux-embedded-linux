 #include <stdio.h>
 #include <unistd.h>
#include <sys/wait.h>

 int main() {
    printf("Start runing process");
    int isfork = fork();
    int status, retVal;
    // parent process
    if(isfork == 0) {
        // child process
        printf("This is child process and have process id is: %d\n", getpid());
        return 0;
    } else if ( isfork > 0) {
        printf("This is parent process and have process id is: %d\n", isfork);
        retVal = wait(&status);
        if (retVal == -1) {
            printf("wait() unsuccessfull\n");
        }
        printf("Im the parent\n");
    }
    return 0;
 }