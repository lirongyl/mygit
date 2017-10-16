/*进程间控制-低级通信*/
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sig_alarm(int sig)
{
	printf("--The signal received is %d.\n",sig);
	signal(SIGINT,SIG_DFL);
}

int main()
{
	signal(SIGINT,sig_alarm);
	while(1){
		printf("wait here!\n");
		sleep(1);
	}
	return 0;
}
