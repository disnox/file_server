/*
************************************************************************
* file name: client/inc/thread.h
* author: 苏尚宇
* date: Sun Feb 12 15:54:34 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/

#ifndef _THREAD_H__
#define _THREAD_H__


extern void thread_init(void *(*start_routine)(void*), void *restrict arg);
extern void *server_recv(void *arg);
extern void *system_client(void *arg);

#endif
