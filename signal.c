#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void my_sig_handler(int signum) {
    printf("Signum = %d\n", signum);
}

int main() {
    int i;
    signal(SIGINT, my_sig_handler);
    for (i = 0; i< 100; i++) {
        sleep(2);
        printf("Hello.\n");
    }
}
