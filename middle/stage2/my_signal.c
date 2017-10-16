#include <stdio.h>
#include <signal.h>

/*********************************************
  *信号处理函数
*********************************************/
void handler_sigint(int signo){
	printf("recv SIGINT\n");
}

int main(void)
{
	signal(SIGINT,handler_sigint);

	while(1);

	return 0;
}

