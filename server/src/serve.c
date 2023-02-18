/*
************************************************************************
* file name: server/src/serve.c
* author: 苏尚宇
* date: Sun Feb 12 15:53:14 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/
#include "main.h"
#include "serve.h"
#include "thread.h"
#include "user_info.h"
#include "control.h"

/*
************************************************************************
* @brief      connect_client_init()
* @param      void
* @return     void
* describe:   客户端初始化
************************************************************************
*/  
int connect_client_init(void)
{
	// 1. 获取一个流式套接字
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		fprintf(stderr, "socket() fail: %s\n", strerror(errno));
		exit(0);
	}
	
	// 2. 绑定ip+port
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;	//ipv4
	saddr.sin_port = htons(50000);	//端口
	saddr.sin_addr.s_addr = inet_addr("192.168.1.93");	//服务器的ip地址
	if( bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1 ) {
		fprintf(stderr, "bind() fail: %s\n", strerror(errno));
		exit(0);
	}
	printf("绑定成功\n");
	
	// 3. 监听（4+2）
	if( listen(sockfd, 2) == -1) {
		fprintf(stderr, "listen() fail: %s\n", strerror(errno));
		exit(0);
	}
	printf("监听成功\n");
	return sockfd;
}
/*
************************************************************************
* @brief      process_data()
* @param      topic: 操作指令 data: 客户端的数据
* @return     void
* describe:   将指令和客户端数据区分开来
************************************************************************
*/  
void process_data(char *topic, char *data)
{
	// char msg[100] = "AT+LoginUser:disnox";
	char *p = NULL, *q = NULL;
	if ( (p = strstr(msg, "AT+")) != NULL) {
		p += 3;
		q = strchr(p, ':');
		memcpy(topic, p, q-p);
		q = strchr(q, ':')+1;
		memcpy(data, q, 100);
		data[strcspn(data, "\n")] = '\0';
		printf("topic:%s  data:%s\n", topic, data);
	}
}
/*
************************************************************************
* @brief      serve()
* @param      topic: 操作指令 data: 客户端的数据
* @return     void
* describe:   判断指令集然后执行相应的操作
************************************************************************
*/  
char user_buf[10];
void serve(char *topic, char *data)
{
	process_data(topic, data);
	/* 验证用户 */
	if ( !(strcmp(topic, "LoginUser")) ) {
		if (find_user_item(find_user_name, data) != NULL) {
			printf("ok\n");
			bzero(user_buf, sizeof(user_buf));
			strcpy(user_buf, data);
		}
	}
	/* 验证密码 */
	if ( !strcmp(topic, "LoginPasswd")) {
		if (find_user_item(find_user_passwd, data) != NULL) {
			write(confd, "1", 1);
			printf("ok\n");
		}
	}
	/* 注册用户 */
	if ( !(strcmp(topic, "LogonUser")) ) {
		mkdir_user(data);
		strcpy(user_buf, data);
	}
	/* 注册密码 */
	if ( !(strcmp(topic, "LogonPasswd")) ) {
		
		add_user_item(user_buf, data);
		traverse_user_list();
		save_user_to_file("doc/user.txt");
	}
	/* 查看文件 */
	if ( !(strcmp(topic, "ViewFile")) ) {
		view_file(&confd, data);
	}
	/* 下载共享文件 */
	if ( !(strcmp(topic, "DownloadPublicFile")) ) {
		send_files(data, "public");
	}
	/* 上传共享文件 */
	if ( !(strcmp(topic, "UploadPublicFile")) ) {
		recv_files(data, "public");
	}
	/* 下载私人文件 */
	if ( !(strcmp(topic, "DownloadPrivateFile")) ) {
		send_files(data, user_buf);
	}
	/* 上传私人文件 */
	if ( !(strcmp(topic, "UploadPrivateFile")) ) {
		recv_files(data, user_buf);
	}
	/* 管理员查看用户 */
	if ( !(strcmp(topic, "CheckUser")) ) {
		send_user_list();
	}
	/* 管理员查看文件 */
	if ( !(strcmp(topic, "CheckFile")) ) {
		print_directory_contents(data);
	}
	/* 删除用户 */
	if ( !(strcmp(topic, "RemoveUser")) ) {
		delete_user(data);
	}
	/* 删除文件 */
	if ( !(strcmp(topic, "RemoveFile")) ) {
		delete_file(data);
	}
}

