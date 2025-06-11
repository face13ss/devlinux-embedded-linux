#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h> // 
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50
#define BUFFER_SIZE 256

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
    int port_no, len, opt;
    int server_sd, new_socket_sd;
    struct sockaddr_in serv_addr, client_addr;

    // read port number on command line
    if (argc < 2) {
        printf("No port provided\ncommand: ./server <port number>\n");
        exit(EXIT_FAILURE);
    } else {
        port_no = atoi(argv[1]);
    }

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    // Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1)
        handle_error("socket()");
    // fprint(stderr, "ERROR on socket(): %s\n", strerror(errno));

    // Stop error: "address already in use"
    // if (setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    //     handle_error("socket()");

    // Init local address for server
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr

    // Bind socket with server IP address
    if(bind(server_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");

    // Max 50 connect in queue
    if (listen(server_sd, LISTEN_BACKLOG) == -1)
        handle_error("listen()");

    len = sizeof(client_addr);

    while (1) {
        printf("Server is listening at port: %d \n....\n", port_no);
        new_socket_sd = accept(server_sd, (struct sockaddr*)&client_addr, (socklen_t *)&len);
        if (new_socket_sd == -1)
            handle_error("accept()");

        system("clear");

        printf("Server: got connection\n");
        chat_func(new_socket_sd);
    }
    close(server_sd);
}