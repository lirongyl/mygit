#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define N 64

int main(int argc,char *argv[])
{
	if(argc < 3){
		printf("Using:%s ip port\n",argv[0]);
		exit(-1);
	}

	int sockfd;
	struct sockaddr_in myaddr,peeraddr;
	char buf[N] = {0};

	size_t n;
	socklen_t mylen,peerlen;
	mylen = sizeof(myaddr);
	peerlen = sizeof(peeraddr);
	/* creat socket */
	if( (sockfd = socket(AF_INET,SOCK_DGRAM,0)) == -1 ){
		printf("socket");
		exit(-1);
	}
	/* bind initialization */
	bzero(&myaddr,sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(atoi(argv[2])+1);
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);
	/* bind */
	if( bind(sockfd,(struct sockaddr *)&myaddr,mylen) == -1){
		perror("bind");
		exit(-1);
	}
	/* connect */
	bzero(&peeraddr,sizeof(peeraddr));
	peeraddr.sin_family = AF_INET;
	peeraddr.sin_port = htons(atoi(argv[2]));
	peeraddr.sin_addr.s_addr = inet_addr(argv[1]);
	while(1){
		fgets(buf,N,stdin);
		printf("buf:%s",buf);
		if( (n = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&peeraddr,peerlen)) == -1 ){
			perror("sendto");
			exit(-1);
		}
		if(strncmp(buf,"quit",4) == 0){
			break;
		}
		printf("n = %d\n",n);
	}
	close(sockfd);
	exit(0);

	return;
}

