#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int count = 0;

void printTime();
void my_sig_handler(int signum);

int main() {
    signal(SIGALRM, my_sig_handler);
    alarm(5);

    while (1) {
        printf("Hello\n");
        sleep(1);
    }

    return 0;
}

void my_sig_handler(int signum) {
    printf("김다진\n");
    printTime();

    count++;
    if (count == 3) {
        exit(0);
    }

    alarm(5);
}

void printTime() {
	time_t ct;
	struct tm tm;
	ct = time (NULL);
	tm = *localtime (&ct);
	printf ("%d-%d-%d hour: %d, min : %d, sec: %d\n",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
		tm.tm_min, tm.tm_sec);
}

