/****************************************
 **	一个简单的时间获取程序
 **	客户端
 ***************************************/
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 4096

int main(int argc,char **argv)
{
	int sockfd,n;
	struct sockaddr_in servaddr;
	char recvline[MAXLINE+1];

	if(argc != 2){
		printf("usage:./test_client <IPaddress>\n");
		exit(0);
	}

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		printf("socket error\n");
		exit(1);
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0){
		printf("inet_pton error\n");
		exit(1);
	}
	if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<=0){
		printf("connect error\n");
		exit(1);
	}
	while((n=read(sockfd,recvline,MAXLINE))>0){
		recvline[n] = 0;
		if(fputs(recvline,stdout) == EOF){
			printf("fputs error\n");
			exit(1);
		}
	}
	if(n < 0){
		printf("read error\n");
		exit(1);
	}
	return 0;
}

