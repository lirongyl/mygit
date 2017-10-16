#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	int client_sockfd;
	int len;
	struct sockaddr_in client_addr;
	int sin_size;
	char buf[BUFSIZ];
	memset(&client_addr,0,sizeof(client_addr));
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//服务器IP地址
	client_addr.sin_port = htons(8000);	//服务器IP地址
	//创建客户端套接字
	if( (client_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0){
		perror("socket error");
		return 1;
	}
	strcpy(buf,"This is a test message");
	printf("sending:'%s'\n",buf);
	sin_size = sizeof(struct sockaddr_in);
	//向服务器发送数据包
	if( (len = sendto(client_sockfd,buf,strlen(buf),0,(struct sockaddr*)&client_addr,sizeof(struct sockaddr))) <0 ){
		perror("recvfrom");
		return 1;
	}
	//关闭套接字
	close(client_sockfd);
	return 0;
}
