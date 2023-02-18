/*
************************************************************************
* file name: control.h
* author: 苏尚宇
* date: Tue Feb 14 21:20:40 CST 2023
* path: /mnt/e/Code/puresoft/project/server
* describe: NULL
************************************************************************
*/

#ifndef _CONTROL_H__
#define _CONTROL_H__

struct filestat {
	char name[20];	// 文件名字
	unsigned size;	// 文件大小
};

extern void convert_timestamp_to_time(long int timestamp, char *timebuf);
extern void mkdir_user(char *data);
extern void view_file(int *confd, char *data);
extern void send_files(char *data, char *file);
extern void recv_files(char *data, char *file);
extern void send_user_list(void);
extern void delete_user(char *data);
extern int delete_directory(const char* dir_path); 
extern void print_directory_contents(const char *path);
extern int delete_file(const char *file_path); 

#endif
