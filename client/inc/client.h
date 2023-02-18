/*
************************************************************************
* file name: client/inc/client.h
* author: 苏尚宇
* date: Sun Feb 12 15:54:40 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/

#ifndef _CLIENT_H__
#define _CLIENT_H__

typedef struct {
    int sockfd;
    char msg[1024*1024];
}_data;

struct filestat {
	char name[20];	// 文件名字
	unsigned size;	// 文件大小
};

extern void connect_serve_init(void);
extern void recv_file_info(void);
extern void recv_files(void);
extern void send_files(int i);


#endif
