/*****************************************************
 **	用于测试字符设备globalfifo
 ** 测试程序待写中
 ** 
 ** 2017-11-02
 ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
/* 自定义的错误处理函数 */
void my_err(const char *err_string,int line)
{
	fprintf(stderr,"line:%d-->",line);
	perror(err_string);
}

/*自定义的写测试函数*/
int my_write(char *write_buf)
{
	int fd;
	int len = 0;

	//打开字符设备
	if( (fd = open("/dev/globalmem",O_RDWR)) == -1){
		my_err("open",__LINE__);
	} else {
		printf("open success!\n");
	}

	//写数据
	if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf)){
		my_err("write",__LINE__);
	} else {
		printf("write data success!\n");
		len = strlen(write_buf);
		printf("len = %d\ndata:%s\n",len,write_buf);
	}

	return fd;
}

void my_read(int fd)
{
	int len = 0;
	char read_buf[64];
	len = lseek(fd,0,SEEK_CUR);
	lseek(fd,0,SEEK_SET);
	//读数据
	if((len = read(fd,read_buf,len)) < 0){
		my_err("read",__LINE__);
	} else {
		printf("read data success! len = %d\n",len);
		printf("%s\n",read_buf);
	}
}

int main(int argc,char **argv)
{
	int fd;
	
	pid_t pid;

	pid = fork();	/*进程的创建*/

	switch(pid){
	case 0:
		printf("--------child process--------\n");
		fd = my_write("Child process write!\0");
		my_read(fd);
		break;
	case -1:
		printf("process create failed!\n");
		break;
	default:
		printf("--------parent process--------\n");
		fd = my_write("I am a parent process write!\0");
		my_read(fd);
		break;
	}
	/* 后获取到文件的进程将不能对文件操作 */	
	close(fd);

	return 0;
}

