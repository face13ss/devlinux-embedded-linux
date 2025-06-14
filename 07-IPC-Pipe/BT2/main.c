#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

 int main() {
    int fds_1[2];
    int fds_2[2];
    int pipeStatus;
    char write_buff[128] = {0};
    

    if ((pipeStatus = pipe(fds_1)) != 0) {
        handle_error("pipe()");
    }
    if ((pipeStatus = pipe(fds_2)) != 0) {
        handle_error("pipe()");
    }

    pid_t child_1 = fork();
    
    int status;
    // parent process
    if(child_1 == 0) {
        // child process
        close(fds_1[1]);
        char buff[128] = {0};
        read(fds_1[0], buff, sizeof(buff));
        printf("Child_1 received message from parent: %s", buff);

        // string cat
        char * message ="And this message from child_1 to child_2\n";
        strcat(buff, message);
        close(fds_2[0]);
        write(fds_2[1], buff, strlen(buff));
        close(fds_2[1]);
        close(fds_1[0]);
        return 0;
    } else if ( child_1 > 0) {
        // Parent
        pid_t child_2 = fork();
        if (child_2 == 0) {
            close(fds_2[1]);
            char buff[128] = {0};
            read(fds_2[0], buff, sizeof(buff));
            printf("Child_2 received message from child_1: %s", buff);

            close(fds_2[0]);
            return 0;
        } else if (child_2 < 0)
        {
            handle_error("faile to create child_2");
        } 
        
        printf("This is parent process and have process id is: %d\n", getpid());
        close(fds_1[0]);
        close(fds_2[0]);
        close(fds_2[1]);
        char* message = "Hello from parent process\n";
        memcpy(write_buff, message, strlen(message) + 1);
        write(fds_1[1], write_buff, strlen(message));

        close(fds_1[1]);
        
        wait(&status);
        printf("Im the parent\n");
    }
    return 0;
 }