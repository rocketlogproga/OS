#include "stdio.h"
#include "unistd.h"
#include "string.h"

int main(){
    int fd[2];      // file descriptors [0]-for read, [1]-for write
    pipe(fd);

    // getting filename from stdin
    char* filename = NULL;
    size_t sizename = 0;
    getline(&filename, &sizename, stdin);
    filename[strlen(filename) - 1] = '\0';

    pid_t pid = fork();     // new process

    if (pid == -1){     // error in fork
        printf("Error fork()");
        return -1;
    }
    // child
    else if (pid == 0){
        close(fd[1]);
        dup2(fd[0], 0);
        execl("./child", "child", filename, (char*) NULL);
    }
    // parent
    else {
        close(fd[0]);
        char ch;
        while (scanf("%c", &ch) != EOF){
            write(fd[1], &ch, sizeof(ch));
        }
        close(fd[1]);
    }

    return 0;
}