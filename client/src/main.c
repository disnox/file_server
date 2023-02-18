/*
************************************************************************
* file name: server/src/thread.c
* author: 苏尚宇
* date: Sun Feb 12 15:53:05 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/
#include "main.h"
#include "client.h"
#include "thread.h"
#include "control.h"
#include "display.h"

int main(int argc, char *argv[])
{
	connect_serve_init();
	
	// thread_init(server_recv, &sockfd);
	thread_init(system_client, NULL);

	while(1)
	{
		// bzero(msg, sizeof(msg));
		// fgets(msg, 100, stdin);
		// write(sockfd, msg, 100);
		if( strncmp(quit, "quit", 4) == 0) {
			printf("----\n");
			break;
		}
			
		// recv_files();
	}
	
	// 5. 关闭通信套接字和监听套接字
	close(sockfd);

	return 0;
}