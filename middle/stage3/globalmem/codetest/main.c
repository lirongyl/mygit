/*****************************************************
 **	用于测试字符设备globalmem
 ** 2017-10-19
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

int main(int argc,char **argv)
{
	int fd;
	char write_buf[32] = "Hello Kernel!";
	char read_buf[64];
	int len = 0;

	//在打开字符设备
	if( (fd = open("/dev/globalmem",O_RDWR)) == -1){
		my_err("open",__LINE__);
	} else {
		printf("open success!\n");
	}

	/*写数据*/
	if(write(fd,write_buf,strlen(write_buf)) != strlen(write_buf)){
		my_err("write",__LINE__);
	} else {
		printf("write data success!\n");
		len = strlen(write_buf);
		printf("len = %d\n",len);
	}

	/*读数据*/
	if( (len = read(fd,read_buf,64)) < 0){
		my_err("read",__LINE__);
	} else {
		printf("read data success!\n");
		printf("%s\n",write_buf);
	}

	close(fd);
	return 0;
}

