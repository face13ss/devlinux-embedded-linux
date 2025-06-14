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
#define SERVER_SOCKET_PATH  "/tmp/my_dgram_socket"
#define CLIENT_SOCKET_PATH "/tmp/my_dgram_client"

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[]){

    int client_sd;
    struct sockaddr_un addr, server_addr;
    socklen_t addr_len;

    char buffer[BUFFER_SIZE];

    // Create client socket
    client_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_sd == -1)
    {
        handle_error("socket()");
        exit(EXIT_FAILURE);
    }

    // Gán địa chỉ cho client (bắt buộc với SOCK_DGRAM)
    unlink(CLIENT_SOCKET_PATH); // Xoá nếu file socket cũ còn
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, CLIENT_SOCKET_PATH);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SERVER_SOCKET_PATH);

    if (bind(client_sd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        handle_error("bind()");
    }

    while (1) {
        addr_len = sizeof(server_addr);

        memset(buffer, 0, BUFFER_SIZE);

        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        sendto(client_sd, buffer, BUFFER_SIZE, 0, (const struct sockaddr *)&server_addr, addr_len);

        if(strncmp("exit", buffer, 4) == 0) {
            system("clear");
            break;
        }

        
        int n = recvfrom(client_sd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);

        if (n < 0)
        {
            perror("recvfrom() failed");
            continue;
        }
        
        printf("Received from Server: %s", buffer);

    }
    close(client_sd);
    unlink(CLIENT_SOCKET_PATH);
    
    return 0;
}