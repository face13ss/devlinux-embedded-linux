#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    
    // build argument array
    int num_args = argc - 2;
    char *argvLS[num_args + 2];

    if (strcmp(argv[1], "1") == 0){
        argvLS[0] = "ls";
    } else if (strcmp(argv[1], "2") == 0) {
        argvLS[0] = "date";
    } else {
        return -1;
    }

    for (int i = 0; i < num_args; i++) {
        argvLS[i + 1] = argv[i + 2];
    }

    argvLS[num_args + 1] = NULL;

    execvp(argvLS[0], argvLS);

    return 1;
    
}