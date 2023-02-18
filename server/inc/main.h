/*
************************************************************************
* file name: server/inc/serve.h
* author: 苏尚宇
* date: Sun Feb 12 15:54:21 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/

#ifndef _MAIN_H__
#define _MAIN_H__

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <dirent.h>


extern struct list_head user_list;
extern int confd;	//通信套接字

#endif
