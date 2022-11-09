#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

pid_t usr1_pid;

void usr2_signal_handler(int signum);

int main() {
    pid_t usr2_pid;

    usr2_pid = getpid();
    printf("usr2 pid = %d\n", usr2_pid);
    printf("usr1 pid = ");
    scanf("%d", &usr1_pid);

    signal(SIGUSR2, usr2_signal_handler);

    while (1) {
        printf("Hello\n");
        sleep(1);
    }

    return 0;
}

void usr2_signal_handler(int signum) {
    printf("Signul %d cought.\n", signum);
    kill(usr1_pid, SIGUSR1);
    exit(0);
}
