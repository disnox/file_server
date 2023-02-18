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
#include "serve.h"
#include "thread.h"

char msg[1024*1024];

/*
************************************************************************
* @brief      cilent_recv()
* @param      arg：线程参数
* @return     void
* describe:   处理客户端信息
************************************************************************
*/  
void *cilent_recv(void *arg) 
{
	char topic[30], data[100];
	
	struct cilent client_info;
	client_info.confd = ((struct cilent *)arg)->confd;
	client_info.ip = ((struct cilent *)arg)->ip;
	client_info.port = ((struct cilent *)arg)->port;
	
	//自动分离线程, 通信结束自动回收资源
	pthread_detach(pthread_self());
	
	// 与客户端通信（收发数据）
	while(1)
	{
		bzero(topic, sizeof(topic));
		bzero(data, sizeof(data));
		bzero(msg, sizeof(msg));
		read(client_info.confd, msg, 1024*1024);
		if( strncmp(msg, "quit", 4) == 0) {
			printf("[%s:%hu]-已退出\n", client_info.ip, client_info.port);
			break;
		}
		printf("from client [%s:%hu]: %s\n", client_info.ip, client_info.port, msg);
		// write(client_info.confd, msg, strlen(msg));
		serve(topic, data);

	}
	
	// 关闭通信套接字和监听套接字
	close(client_info.confd);
	
	//退出线程
	pthread_exit(NULL);
}
