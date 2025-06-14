#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h> // 
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/un.h>

#define SERVER_SOCKET_PATH  "/tmp/my_dgram_socket"
#define CLIENT_SOCKET_PATH "/tmp/my_dgram_client"
#define BUFFER_SIZE 256

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    int sock_sd;
    struct sockaddr_un addr, client_addr;
    socklen_t addr_len;
    char buffer[BUFFER_SIZE];

    unlink(SERVER_SOCKET_PATH);


    // Create socket
    sock_sd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sock_sd == -1) {
        handle_error("socket()");
        exit(EXIT_FAILURE);
    }
        


    // Init local address for server
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SERVER_SOCKET_PATH);

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, CLIENT_SOCKET_PATH);

    // Bind socket with server IP address
    if(bind(sock_sd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        handle_error("bind()");
        exit(EXIT_FAILURE);
    }
        

    while (1) {
        addr_len = sizeof(client_addr);
        memset(buffer, 0, BUFFER_SIZE);

        int n = recvfrom(sock_sd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        buffer[n] = '\0';

        if (n < 0)
        {
            perror("recvfrom() failed");
            continue;
        }
        
        
        printf("Received from client: %s", buffer);
        
        memset(buffer, 0, BUFFER_SIZE);
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if(strncmp("exit", buffer, 4) == 0) {
            system("clear");
            break;
        }

        sendto(sock_sd, buffer, n, 0, (const struct sockaddr *)&client_addr, addr_len);


    }
    close(sock_sd);
    unlink(SERVER_SOCKET_PATH);
    return 0;
}