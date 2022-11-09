#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void child_task() {
    char *arglist[10];
    char buf[100];
    int i;

    i = 0;
    while (i < 10) {
        printf("Dajin Kim Arg[%d]? ", i);
        gets(buf);
        arglist[i] = (char*) malloc(strlen(buf) + 1);
        strcpy(arglist[i], buf);
        if (strcmp(arglist[i], "") == 0) {
            arglist[i] = NULL;
            break;
        }
        i++;
    }
    execvp(arglist[0], arglist);
}

int main() {
    pid_t childId;
    int i;

    while (1) {
        childId = fork();
        switch (childId) {
            case -1:
                perror("fork failed.");
                break;
            // child process
            case 0:
                child_task();
                break;
            // parent process
            default:
                wait();
        }
    }

    return 0;
}
