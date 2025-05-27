#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    // build argument array
    char *argvLS[argc];

    for (int i = 0; i < argc ; i++) {
            if (i == 0) {
                continue;
            }
            if (i == argc - 1) {
                argvLS[i] = NULL;
                break;
            }
            argvLS[i] = argv[i + 1];
        }

    if (strcmp(argv[1], "1") == 0)
    {
        argvLS[0] = "ls";
        execvp("ls", argvLS);
        return 0;

    } else if (strcmp(argv[1], "2") == 0)
    {
        argvLS[0] = "date";
        execvp("date", argvLS);
        return 0;
    }
        return -1;
    
}