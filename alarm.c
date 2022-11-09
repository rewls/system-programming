#include <stdio.h>
#include <signal.h>

void my_sig_handler (int signum)
{
	printf ("signum = %d \n", signum);
	printf ("Signal is caught. \n");
	alarm (5);
}

int main ()
{
	signal (SIGALRM, my_sig_handler);
	alarm (5);
	while (1) {
		printf ("Hello\n");
		sleep (2);
	}
}
