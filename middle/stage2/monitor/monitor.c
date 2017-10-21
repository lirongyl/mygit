#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc,char *argv[],char **environ)
{
	int fd[2];
	pid_t pid;
	int stat_val;

	if(argc < 2){
		printf("wrong parameters \n");
		exit(0);
	}
	if(pipe(fd)){
		perror("pipe failed!\n");
		exit(1);
	}

	pid = fork();

	switch(pid){
		case -1:
			perror("fork failed!\n");
			exit(1);
		case 0:
			close(0);
			dup(fd[0]);
			execve("ctrlpocess",(void *)argv,environ);
			exit(0);
		default:
			close(fd[0]);
			/*将命令行第一个参数写进管道*/
			if(write(fd[1],argv[1],strlen(argv[1]))==-1){
				printf("write failed\n");
			}else{
				printf("write success!\n");
			}
			break;
	}
	wait(&stat_val);
	exit(0);
}
