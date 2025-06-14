#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int returnForkValue;
    int status;
    pid_t pid;

    returnForkValue = fork();
    if (returnForkValue == -1) {
        printf("faild");
    } else if (returnForkValue == 0) {
        printf ("child process: %d\n",getpid());
        sleep(10);
        printf ("child process: exited");
    } else {
        printf("Parent process (PID: %d) is terminating.\n", getpid());
        exit(0);
    }
    return 0;
}
