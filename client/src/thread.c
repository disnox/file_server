/*
************************************************************************
* file name: client/src/thread.c
* author: 苏尚宇
* date: Sun Feb 12 15:53:34 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/
#include "main.h"
#include "thread.h"
#include "client.h"
#include "control.h"
#include "system.h"

/*
************************************************************************
* @brief      thread_init()
* @param      start_routine: 任务函数名称
*			  arg: 线程参数
* @return     void
* describe:   添加任务
************************************************************************
*/  
void thread_init(void *(*start_routine)(void*), void *restrict arg)
{
	pthread_t thread;
    int ret;
    ret = pthread_create(&thread, NULL, start_routine, arg);
    if (ret != 0) {
        printf("Failed to create thread\n");
        exit(1);
    }
}
/*
************************************************************************
* @brief      thread_init()
* @param      arg: 线程参数  
* @return     void
* describe:   菜单任务线程
************************************************************************
*/  
void *system_client(void *arg)
{
	while(1)
	{
		system_control();
		if( strncmp(quit, "quit", 4) == 0)
			break;
	}
	pthread_exit(NULL);
}


