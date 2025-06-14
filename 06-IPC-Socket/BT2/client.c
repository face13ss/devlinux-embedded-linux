#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h> // 
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 256

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]){
    int server_port;
    char server_addr[16] = {0};
    int client_sd;
    struct sockaddr_in serv_addr, client_addr;
    socklen_t len;
    char buffer[BUFFER_SIZE];


    // read port number on command line
    if (argc < 3) {
        printf("No IP address and port provided\ncommand: ./client <server address> <port number>\n");
        exit(EXIT_FAILURE);
    } else {
        strcpy(server_addr, argv[1]);
        server_port = atoi(argv[2]);
    }

    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    memset(&client_addr, 0, sizeof(struct sockaddr_in));

    // Create client socket
    client_sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_sd == -1)
        handle_error("socket()");

    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, server_addr, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(server_port);

    while (1) {
        len = sizeof(client_addr);

        memset(buffer, 0, BUFFER_SIZE);

        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        sendto(client_sd, buffer, BUFFER_SIZE, 0, (const struct sockaddr *)&serv_addr, len);

        if(strncmp("exit", buffer, 4) == 0) {
            system("clear");
            break;
        }

        
        int n = recvfrom(client_sd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serv_addr, &len);

        if (n < 0)
        {
            perror("recvfrom() failed");
            continue;
        }
        
        printf("Received from Server: %s", buffer);

    }
    
    return 0;
}