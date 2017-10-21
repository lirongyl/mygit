#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int arg,char *argv[],char **environ)
{
	int n;
	char buf[1024];

	printf("----------------ctrlpocess is running-------------------\n");

	printf("argv = %s\n",argv[1]);

	if( (n = read(0,buf,1024)) > 0){
		buf[n] = '\0';
		printf("ctrlpocess receive:%s\n",buf);

		if(!strcmp(buf,"exit")){
				exit(0);
		}
		if(!strcmp(buf,"getpid")){
			printf("my pid:%d\n",getpid());
			sleep(3);
			exit(0);
		}
	}else{
		perror("read failed!\n");
	}
	exit(0);
}

