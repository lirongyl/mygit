/* udp_server.c */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	int server_sockfd;
	int len;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	int sin_size;

	char buf[BUFSIZ];	//数据接收缓存区
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(8000);

	/* 创建服务器端套接字--IPV4协议，面向无连接通信，UDP协议 */
	if((server_sockfd = socket(PF_INET,SOCK_DGRAM,0)) < 0){
		perror("socket error");
		return 1;
	}
	/* 将套接字绑定到服务器的网络地址上 */
	if( bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr)) < 0){
		perror("bind error");
		return 1;
	} 
	sin_size = sizeof(struct sockaddr_in);
	printf("waiting for a packet...\n");
	/*接收客户端的数据并将其发送给客户端 */
	if( (len = recvfrom(server_sockfd,buf,BUFSIZ,0,(struct sockaddr *)&client_addr,&sin_size)) < 0){
		perror("recvfrom error");
		return 1;
	}
	printf("received packet from %s:\n",inet_ntoa(client_addr.sin_addr));
	buf[len] = '\0';
	printf("contents:%s\n",buf);
	/*关闭套接字*/
	close(server_sockfd);
	return 0;
}

