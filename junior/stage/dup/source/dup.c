#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//自定义的错误处理函数
void my_err(const char *err_string,int line)
{
	fprintf(stderr,"line:%d ",line);
	perror(err_string);
	exit(1);
}

int main()
{
	int dup2fd;
	int fd;
	int dupfd;

	if((fd = open("example",O_CREAT|O_TRUNC|O_RDWR,S_IRWXU)) == -1){
		my_err("open",__LINE__);
	}else{
		printf("file open success! fd = %d\n",fd);
	}
	
	if((dupfd = dup(fd)) == -1){
		my_err("dup",__LINE__);
	}else {
		printf("file dup success! dupfd = %d\n",dupfd);
	}

	if((dup2fd = dup2(fd,0)) == -1){
		my_err("dup2",__LINE__);
	}else{
		printf("file dup2 success! dup2fd = %d\n",dup2fd);
	}

	printf("\n");

	return 0;
}

