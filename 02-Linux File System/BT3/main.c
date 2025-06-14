#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) < 0) {
        perror("stat failed");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    // Loại file __mode_t??
    printf("Size: %ld bytes\n", fileStat.st_size);
    printf("Last status change: %s", ctime(&fileStat.st_ctime));

    return 0;
}
