/*
************************************************************************
* file name: client/src/thread.c
* author: 苏尚宇
* date: Sun Feb 12 15:53:34 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/
#include "serve.h"
#include "thread.h"
#include "main.h"
#include "user_info.h"

struct list_head user_list;
int confd;	//通信套接字

int main(int argc, char *argv[])
{
	// process_data(topic, data);
	// printf("topic:%s  data:%s\n", topic, data);

	init_user_list();

	int sockfd = connect_client_init();
	// 4. 等待客户端连接
	struct sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	struct cilent cilent_info;
	pthread_t tid;

	while(1)
	{
		if( (confd = accept(sockfd, (struct sockaddr *)&caddr, &len)) == -1 ) {
			fprintf(stderr, "accept() fail: %s\n", strerror(errno));
			exit(0);
		}
		printf("连接成功: [%s:%hu]\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
		cilent_info.confd = confd;	//刚连接成功的客户端通信套接字
		cilent_info.ip = inet_ntoa(caddr.sin_addr);	//刚连接成功的客户端ip
		cilent_info.port = ntohs(caddr.sin_port);	//刚连接成功的客户端端口
		
		pthread_create(&tid, NULL, cilent_recv, (void *)&cilent_info);
	}
	
	//关闭监听套接字
	close(sockfd);

	return 0;
}