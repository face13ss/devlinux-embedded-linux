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

int main(int argc, char *argv[])
{
    int port_no;
    int server_sd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t len;

    char buffer[BUFFER_SIZE];

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
    server_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sd == -1)
        handle_error("socket()");

    int opt = 1;
    if (setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        handle_error("setsockopt()");


    // Init local address for server
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_no);
    serv_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr

    // Bind socket with server IP address
    if(bind(server_sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        handle_error("bind()");

    while (1) {
        len = sizeof(client_addr);
        memset(buffer, 0, BUFFER_SIZE);

        int n = recvfrom(server_sd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &len);

        if (n < 0)
        {
            perror("recvfrom() failed");
            continue;
        }
        
        printf("Received from client: %s", buffer);
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if(strncmp("exit", buffer, 4) == 0) {
            system("clear");
            break;
        }

        sendto(server_sd, buffer, n, 0, (const struct sockaddr *)&client_addr, len);


    }
    close(server_sd);
    return 0;
}