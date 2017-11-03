/***************************************
 **	一个简单的时间获取程序
 **	服务器端
 ***************************************/
#include <strings.h>
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
	int listenfd,connfd;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family =  AF_INET;
	servaddr.sin_addr.s_addr = htons(INADDR_ANY);
	servaddr.sin_port = htons(13);	/*daytime server*/

	bind(listenfd,(const struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(listenfd,5);
	while(1){
		connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);

		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		write(connfd,buff,strlen(buff));
		close(connfd);
	}
	return 0;
}

