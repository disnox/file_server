/*
************************************************************************
* file name: food_info.c
* author: 苏尚宇
* date: Fri Dec 23 09:56:17 CST 2022
* path: /mnt/e/Code/puresoft/名字-项目名称/源码
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "user_info.h"

/*
************************************************************************
* @brief      init_user_list()
* @param      void
* @return     void
* describe:   初始化用户链表
************************************************************************
*/  
void init_user_list(void)
{
	INIT_LIST_HEAD(&user_list);
	load_user_from_file("doc/user.txt");
	traverse_user_list();
}

/*
************************************************************************
* @brief      add_user_item()
* @param      name: 用户名
*			  passwd: 密码
* @return     void
* describe:   添加用户
************************************************************************
*/  
void add_user_item(char *name, char *passwd)
{
	kernel_list_node *item = (kernel_list_node *)malloc(sizeof(kernel_list_node));

	strcpy(item->user_info.name, name);
	strcpy(item->user_info.passwd, passwd);

	list_add_tail(&(item->point_node), &user_list);
}
/*
************************************************************************
* @brief      traverse_user_list()
* @param      void
* @return     void
* describe:   遍历用户
************************************************************************
*/  
void traverse_user_list(void)
{
	struct list_head *pos;
	kernel_list_node *item;

	list_for_each(pos, &user_list)
	{
		item = list_entry(pos, kernel_list_node, point_node);
		printf("%s\t%s\n", item->user_info.name, item->user_info.passwd);
	}
}
/*
************************************************************************
* @brief      load_user_from_file()
* @param      filename: 文件名
* @return     void
* describe:   从文件中读取用户并添加到链表中
************************************************************************
*/  
void load_user_from_file(const char *filename)
{
	FILE *fp = fopen(filename, "r+");
	if (fp == NULL) {
		fprintf(stderr, "Error: Unable to open file %s\n", filename);
		return;
	}

	char name[30], passwd[30];
	while (fscanf(fp, "%s%s", name, passwd) == 2) {
		add_user_item(name, passwd);
	}

	fclose(fp);
}

/*
************************************************************************
* @brief      find_user_item()
* @param      handle: 回调函数 arg: 用户名称或者密码
* @return     kernel_list_node: 菜单项的地址
* describe:   查找菜单项
************************************************************************
*/  
kernel_list_node *find_user_item(fun_t handle, char *arg)
{
	struct list_head *pos;
	kernel_list_node *item;

	list_for_each(pos, &user_list)
	{
		item = list_entry(pos, kernel_list_node, point_node);
		if ( handle(item, arg) != NULL ) {
			printf("%s\t%s\n", item->user_info.name, item->user_info.passwd);
			return item;
		}
	}

	return NULL;
}

/* 查找用户名回调函数 */
void *find_user_name(kernel_list_node *item, char *arg)
{
	if( !strcmp(item->user_info.name, arg) )
		return item;
	return NULL;
}

/* 查找用户密码回调函数 */
void *find_user_passwd(kernel_list_node *item, char *arg)
{
	if( !strcmp(item->user_info.passwd, arg) )
		return item;
	return NULL;
}
/*
************************************************************************
* @brief      delete_user_item()
* @param      name: 用户名
* @return     void
* describe:   删除用户
************************************************************************
*/  
void delete_user_item(char *name)
{
    kernel_list_node *item = find_user_item(find_user_name, name);
    if (item == NULL) {
        printf("User %s not found\n", name);
        return;
    }
    list_del(&(item->point_node));
    free(item);
    printf("User %s deleted\n", name);
}
/*
************************************************************************
* @brief      save_user_to_file()
* @param      filename: 文件名
* @return     void
* describe:   将修改后的内容写入文件
************************************************************************
*/  
void save_user_to_file(const char *filename)
{
	FILE *fp = fopen(filename, "w+");
	if (fp == NULL) {
		fprintf(stderr, "Error: Unable to open file %s\n", filename);
		return;
	}

	struct list_head *pos;
	kernel_list_node *item;

	list_for_each(pos, &user_list)
	{
		item = list_entry(pos, kernel_list_node, point_node);
		fprintf(fp, "%s\t%s\n", item->user_info.name, item->user_info.passwd);
	}

	fclose(fp);
}

