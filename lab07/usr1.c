#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void usr1_signal_handler(int signum);

int main() {
    pid_t usr1_pid, usr2_pid;

    usr1_pid = getpid();
    printf("usr1 pid = %d\n", usr1_pid);
    printf("usr2 pid = ");
    scanf("%d", &usr2_pid);

    signal(SIGUSR1, usr1_signal_handler);

    kill(usr2_pid, SIGUSR2);

    while (1) {
        printf("Hello\n");
        sleep(1);
    }

    return 0;
}

void usr1_signal_handler(int signum) {
    printf("Signul %d cought.\n", signum);
    exit(0);
}
