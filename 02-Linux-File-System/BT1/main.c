#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    int numb_write;
    char str1[12] = "Hello world";
    char str2[12] = "Put in head";

    fd = open("textfile.txt", O_RDWR | O_APPEND);

    if (fd == -1) {
        printf("Open file failed");
        return 1;
    }

    numb_write = write(fd, str1, strlen(str1));

    lseek(fd, 0, SEEK_SET);

    numb_write = write(fd, str2, strlen(str2));

    close(fd);

    return 0;
}