#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h> // 
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>

#define BUFFER_SIZE 256
#define SOCKET_PATH "/tmp/mysocket"

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void chat_func(int socket_sd)
{
    int numb_read, numb_write;
    char sendbuff[BUFFER_SIZE];
    char recvbuff[BUFFER_SIZE];

    while(1) {
        memset(sendbuff, '0', BUFFER_SIZE);
        memset(recvbuff, '0', BUFFER_SIZE);

        printf("Client: ");
        fgets(sendbuff, BUFFER_SIZE, stdin);

        // response from keyboard through write function
        numb_write = write(socket_sd, sendbuff, sizeof(sendbuff));
        if(numb_write == -1)
            handle_error("write()");
        
        if(strncmp("exit", sendbuff, 4) == 0) {
            system("clear");
            break;
        }

        sleep(1);

        // Read data from socket
        // read function will block until read data
        numb_read = read(socket_sd, recvbuff, BUFFER_SIZE);
        if(numb_read == -1)
            handle_error("read()");
        if(strncmp("exit", recvbuff, 4) == 0) {
            system("clear");
            break;
        }
        printf("\nMessage from Server: %s\n", recvbuff);


    }
    close(socket_sd);
}

int main(int argc, char *argv[]){
    int server_port, con;
    int client_sd;
    struct sockaddr_un addr;


    // Create client socket
    client_sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_sd == -1) {
        handle_error("socket()");
        exit(EXIT_FAILURE);
    }
        

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    if (connect(client_sd,(struct sockaddr*)&addr, sizeof(addr)) == -1)
        handle_error("connect()");

    chat_func(client_sd);
    
    return 0;
}