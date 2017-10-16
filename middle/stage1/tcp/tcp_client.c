/* tcp_client.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define portnumber 3333

int main(int argc,char *argv[])
{
	int sockfd;
	char buffer[1024];
	struct sockaddr_in server_addr;
	struct hostent * host;
	if(argc != 2){
		fprintf(stderr,"Usage:%s hostname\a\n",argv[0]);
		exit(1);
	}
	if((host = gethostbyname(argv[1])) == NULL){
		fprintf(stderr,"gethostname error\n\a");
		exit(1);
	}

	while(1){
	/* 客户端开始建立sockfd描述符 */
	if( (sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1){
		fprintf(stderr,"socket error %s\a\n",strerror(errno));
		exit(1);
	} 
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnumber);
	server_addr.sin_addr = *(struct in_addr *)host->h_addr;
	/* 客户端发起连接 */
	if( connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) == -1){
		fprintf(stderr,"connect error %s\a\n",strerror(errno));
		exit(1);
	}
	/* 连接成功 */
	printf("Please input char:\n");
	/* 发送字符 */
	fgets(buffer,1024,stdin);
	write(sockfd,buffer,strlen(buffer));
	/* 结束通讯 */
	close(sockfd);}
	exit(0);
}
