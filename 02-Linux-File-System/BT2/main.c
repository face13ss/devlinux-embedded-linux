#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // ./example_program filename num-bytes [r/w] "Hello"
    // argv[1] - filename
    // argv[2] - num-bytes
    // argv[3] - [r/w]
    // argv[4] - "Hello"

    if ( argc < 5) {
        // printf("%s\n", argv[0]);
        return 1;
    }

    int fd = -1;

    if (strcmp(argv[3], "r") == 0) {
        // Read from file
        fd = open(argv[1], O_RDONLY);

        if (fd < 0) {
            perror("Open file failed");
            return 1;
        }

        int num_bytes = atoi(argv[2]) + 1;
        char *buff = malloc(num_bytes + 1);
        if (!buff) {
            perror("Memory allocation failed");
            close(fd);
            return 1;
        }

        int numb_read = read(fd, buff, num_bytes);

        if (numb_read == -1) {
            perror("Read failed");
            free(buff);
            close(fd);
            return 1;
        }

        buff[numb_read] = '\0';
        printf("Read (%d bytes): %s\n", numb_read, buff);

        free(buff);
        close(fd);

    } else if (strcmp(argv[3], "w") == 0) {
        // Write in file
        fd = open(argv[1], O_CREAT | O_RDWR);

        if (fd == -1) {
            perror("Open file failed");
            return 1;
        }

        int num_bytes = atoi(argv[2]) + 1;
        int size_buff = strlen(argv[4]);
        if (num_bytes > size_buff) {
            perror("byte write to long!");
        }

        int numb_write= write(fd, argv[4], num_bytes);
        if (numb_write == -1) {
            perror("Write failed");
            close(fd);
            return 1;
        }


        printf("Write (%d bytes): %s\n", numb_write, argv[4]);

        close(fd);
    }

    return 0;
}