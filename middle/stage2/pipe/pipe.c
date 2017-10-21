/******************************************************************
**  管道的创建，对管道的读写 
**	父进程写入数据到管道，子进程读取数据
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define READ_SIZE 100

//读管道
void read_from_pipe(int fd)
{
	char message[READ_SIZE];

	if((read(fd,message,READ_SIZE)) == -1){
		printf("read failed!\n");
	} else {
		printf("read from pipe:%s\n",message);
	}
}

//写管道
void write_to_pipe(int fd)
{
	char *message = "Hello,pipe!\n";
	int len = 0;
	len = strlen(message) + 1;
	if((write(fd,message,len) ) != len){
		printf("write failed!\n");
	} else {
		printf("write successed! date:%s\n",message);
	}
}

int main(void)
{
	int fd[2];				/*定义两个文件的描述符，用于管道*/
	pid_t pid;

	if(pipe(fd)){
		printf("create pipe failed!\n");
		exit(1);
	}else{
		printf("create pipe successed!\n");
	}

	pid = fork();		//创建子进程

	switch(pid){
	case 0:
		close(fd[1]);		//子进程关闭fd1
		read_from_pipe(fd[0]);
		exit(0);
	case -1:
		printf("fork error!\n");
		exit(1);
	default:
		close(fd[0]);		//父进程关闭fd0
		write_to_pipe(fd[1]);
		exit(0);
	}
	return 0;
}

