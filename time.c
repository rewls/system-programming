#include <stdio.h>
#include <time.h>

int main ()
{
	time_t ct;
	struct tm tm;
	ct = time (NULL);
	tm = *localtime (&ct);
	printf ("%d-%d-%d hour: %d, min : %d, sec: %d\n",
		tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
		tm.tm_min, tm.tm_sec);

}
