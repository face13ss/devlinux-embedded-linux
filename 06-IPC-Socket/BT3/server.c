#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>

#define LISTEN_BACKLOG 50
#define BUFFER_SIZE 256

#define SOCKET_PATH "/tmp/mysocket"

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void chat_func(int new_socket_sd)
{
    int numb_read, numb_write;
    char sendbuff[BUFFER_SIZE];
    char recvbuff[BUFFER_SIZE];

    while(1) {
        memset(sendbuff, '0', BUFFER_SIZE);
        memset(recvbuff, '0', BUFFER_SIZE);

        // Read data from socket
        // read function will block until read data
        numb_read = read(new_socket_sd, recvbuff, BUFFER_SIZE);
        if(numb_read == -1)
            handle_error("read()");
        if(strncmp("exit", recvbuff, 4) == 0) {
            system("clear");
            break;
        }
        printf("\nMessage from Client: %s\n", recvbuff);
        
        printf("Server: ");
        fgets(sendbuff, BUFFER_SIZE, stdin);

        // response from keyboard through write function
        numb_write = write(new_socket_sd, sendbuff, sizeof(sendbuff));
        if(numb_write == -1)
            handle_error("write()");
        
        if(strncmp("exit", sendbuff, 4) == 0) {
            system("clear");
            break;
        }

        sleep(1);
    }
    close(new_socket_sd);
}



int main(int argc, char *argv[])
{
    int server_sd, new_socket_sd, len;
    struct sockaddr_un serv_addr, client_addr;


     unlink(SOCKET_PATH);

    // Create socket
    server_sd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sd == -1) {
        handle_error("socket()");
        exit(EXIT_FAILURE);
    }
        
    memset(&serv_addr, 0, sizeof(serv_addr));


    // Init local address for server
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, SOCKET_PATH);

    // Bind socket with server IP address
    if(bind(server_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        handle_error("bind()");
        exit(EXIT_FAILURE);
    }
        

    // Max 50 connect in queue
    if (listen(server_sd, LISTEN_BACKLOG) == -1)
        handle_error("listen()");

    len = sizeof(client_addr);

    while (1) {
        printf("Server is listening\n....\n");
        new_socket_sd = accept(server_sd,NULL , NULL);
        if (new_socket_sd == -1)
            handle_error("accept()");

        system("clear");

        printf("Server: got connection\n");
        chat_func(new_socket_sd);
    }
    close(server_sd);
}