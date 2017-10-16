#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 64

typedef struct sockaddr SA;

int main(int argc,char *argv[])
{
	if(argc < 3){
		printf("Using:%s ip port\n",argv[0]);
		exit(-1);
	}

	int listenfd,connfd;
	struct sockaddr_in myaddr,peeraddr;
	char buf[N]={0};
	size_t n;
	socklen_t mylen,peerlen;
	mylen = sizeof(myaddr);
	peerlen = sizeof(peeraddr);
	/* creat socket */
	if( (listenfd = (socket(PF_INET,SOCK_DGRAM,0))) < 0){
		perror("socket");
		exit(-1);
	}
	/* bind initialization */
	bzero(&myaddr,mylen);
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	inet_aton(argv[1],&myaddr.sin_addr);

	if( bind(listenfd,(SA *)&myaddr,sizeof(myaddr)) < 0 ){
		perror("bind");
		exit(-1);
	}
	/* listen */
	listen(listenfd,5);
	/* accept */
	if( (connfd = accept(listenfd,(SA *)&peeraddr,&peerlen)) == -1 ){
		perror("accept");
		exit(-1);
	}
	printf("connect from %s:%d\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port));
	/* recv-send */
	while(1){
		n = recv(connfd,buf,N,0);
		buf[n] = 0;
		printf("n = %d--%s\n",n,buf);
		if(strncmp(buf,"quit",4) == 0){
			break;
		}
		send(connfd,buf,strlen(buf),0);
	}
	close(connfd);
	close(listenfd);
	exit(0);
}
