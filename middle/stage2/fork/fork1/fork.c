/*创建一个进程*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	printf("Process Creation Study\n");
	pid = fork();
	switch(pid){
	case 0:
		printf("Child process is running,CurPid is %d,ParentPid is %d\n",pid,getppid());
		break;
	case -1:
		perror("Process creation failed\n");
		break;
	default:
		printf("Parent process is runing,ChildPid is %d,ParentPid is %d\n",pid,getppid());
		break;
	}
	exit(0);
	return 0;
}
