#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main ()
{
	char *arglist[10];
	char buf[100];
	int i;
	i = 0;
	while (i < 10) {
		printf ("Arg[%d]? ", i);
		gets (buf);
		arglist[i] = (char*) malloc (strlen(buf) + 1);
		strcpy (arglist[i], buf);
		if (strcmp (arglist[i], "") == 0) {
			arglist[i] = NULL;
			break;
		}
		i++;
	}
	execvp (arglist[0], arglist);
}
