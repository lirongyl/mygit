#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	char *msg;
	int k;

	printf("Process Creation Study\n");
	pid = fork();
	switch(pid){
	case 0:
		msg = "Chile process is running";
		k = 3;
		break;
	case -1:
		perror("Process Creation failed\n");
		break;
	default:
		msg = "Parent process is running";
		k = 5;
		break;
	}

	while(k > 0){
		puts(msg);
		sleep(3);
		k--;
	}
	return 0;
}
