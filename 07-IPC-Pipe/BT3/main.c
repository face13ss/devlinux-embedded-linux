#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

 int main() {
    int fds[2];
    int pipeStatus;
    char write_buff[128] = {0};
    char read_buff[128] = {0};

    if ((pipeStatus = pipe(fds)) != 0) {
        handle_error("pipe()");
    }

    pid_t isfork = fork();
    int status, retVal;
    // parent process
    if(isfork == 0) {
        // child process
        close(fds[1]);
        read(fds[0], read_buff, sizeof(read_buff));
        printf("Message from parent: %s have length is %zu\n",read_buff, strlen(read_buff));
        close(fds[0]);
        return 0;
    } else if ( isfork > 0) {
        close(fds[0]);
        char* message = "Hello from parent process";
        memcpy(write_buff, message, strlen(message) + 1);
        write(fds[1], write_buff, strlen(message));

        close(fds[1]);
        
        wait(&status);
        printf("Im the parent\n");
    }
    return 0;
 }