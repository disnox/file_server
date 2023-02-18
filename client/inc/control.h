/*
************************************************************************
* file name: control.h
* author: 苏尚宇
* date: Mon Feb 13 20:40:58 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/

#ifndef _CONTROL_H__
#define _CONTROL_H__

typedef struct {
    char name[20];
    char passwd[20];
}_user;

extern int sockfd;
extern char quit[10];
extern char command[][30];
extern _user end_user;

extern void login_user(void);
extern void logon_user(void);

extern void view_file(char *file_buf);
extern void down_upload_file(int i);

extern void admin_user(void);
extern void admin_file(void);

extern void exit_enter(void);
extern void sign_out(void);

#endif
