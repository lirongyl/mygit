#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int fd;
	if ((fd = open("test.txt",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR)) == -1)
	{
		perror("open");
		exit(1);
	}
	else
	{
		printf("create file success\n");
	}
	close(fd);
	return 0;
}

