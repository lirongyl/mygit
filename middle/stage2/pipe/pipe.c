/* 管道的创建，对管道的读写 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//读管道
void read_from_pipe(int fd)
{
	char message[100];
	read(fd,message,100);
	printf("read from pipe:%s\n",message);
}

//写管道
void write_to_pipe(int fd)
{
	char *message = "Hello,pipe!\n";
	write(fd,message,strlen(message)+1);
}

int main(void)
{
	int fd[2];
	pid_t pid;
	int stat_val;


	if(pipe(fd)){
		printf("create pipe failed!\n");
		exit(1);
	}

	pid = fork();
	switch(pid){
	case 0:
		close(fd[1]);		//子进程关闭fd1
		read_from_pipe(fd[0]);
		exit(0);
	case -1:
		printf("fork error!\n");
		exit(1);
	default:
		close(fd[2]);		//父进程关闭fd2
		write_to_pipe(fd[1]);
		exit(0);
	}
	return 0;
}

