#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// Define signal handlers here.

int fd;

void catch_signal(int sig)
{
	if(sig == SIGRTMIN)
		write(fd, "0", 1);
	else if(sig == SIGRTMIN+1)
		write(fd, "1", 1);	
	else if(sig == SIGRTMIN+2)
		write(fd, "2", 1);
	else if(sig == SIGRTMIN+3)
		write(fd, "3", 1);
	else if(sig == SIGTERM)
	{
		close(fd);
		exit(0);
	}
}


int main()
{
	// Register signal handlers here.
	
	fd = open("/dev/rps", O_WRONLY);
	signal(SIGRTMIN, catch_signal);
	signal(SIGRTMIN+1, catch_signal);
	signal(SIGRTMIN+2, catch_signal);
	signal(SIGRTMIN+3, catch_signal);
	signal(SIGTERM, catch_signal);
	while(1) pause();
 	return 0;
}
