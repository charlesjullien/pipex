#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	char *str = NULL;
	pid_t pid;
	printf("tout debut, pid = %d\n", pid);
	str = "parent";
	pid = fork();
	if (pid == 0)
	{
		str = "child";
		printf("i am the %s\n", str);
	}
	else
	{
		printf("i am the %s\n", str);
		wait(NULL);	
	}
	printf("fin, pid = %d avec %s\n", pid, str);
	return (0);
}
