/*
************************************************************************
* file name: server/inc/serve.h
* author: 苏尚宇
* date: Sun Feb 12 15:54:21 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/

#ifndef _SERVE_H__
#define _SERVE_H__

 //客户端信息
struct cilent
{
	int confd;
	char *ip;
	unsigned short port;
};

extern char user_buf[10];

extern int connect_client_init(void);
extern void process_data(char *topic, char *data);
extern void serve(char *topic, char *data);



#endif
