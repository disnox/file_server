/*
************************************************************************
* file name: food_info.h
* author: 苏尚宇
* date: Fri Dec 23 09:56:27 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#ifndef _USER_INFO_H__
#define _USER_INFO_H__

#include "kernel_list.h"

extern struct list_head user_list;

typedef struct {
    char name[30];          // 用户名
    char passwd[30];        // 密码
}user_item_t;

typedef struct {
    user_item_t user_info;          // 菜单结构体
    struct list_head point_node;    // 内核链表
}kernel_list_node;

typedef void *(*fun_t)(kernel_list_node *, char *);

extern void init_user_list(void);
extern void add_user_item(char *name, char *passwd);
extern void traverse_user_list(void);
extern void load_user_from_file(const char *filename);

extern kernel_list_node *find_user_item(fun_t handle, char *arg);
extern void *find_user_name(kernel_list_node *item, char *arg);
extern void *find_user_passwd(kernel_list_node *item, char *arg);

extern void delete_user_item(char *name);
extern void save_user_to_file(const char *filename);

#endif
