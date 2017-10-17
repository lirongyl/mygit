#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	umask(0);		//不屏蔽任何权限
	if(creat("example.txt",S_IRWXU|S_IRWXG|S_IRWXO) < 0){
		perror("creat");
		exit(1);
	}

	umask(S_IRWXO);	//屏蔽其他用户的所有权限
	if(creat("test.txt",S_IRWXU|S_IRWXG|S_IRWXO) < 0){
		perror("creat");
		exit(1);
	}
	return 0;
}

