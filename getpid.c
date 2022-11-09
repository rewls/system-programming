#include <stdio.h>
#include <sys/types.h>

int main ()
{
	pid_t pid;
	pid = getpid ();
	printf ("pid = %d \n", pid);
}
