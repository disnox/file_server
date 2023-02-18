/*
************************************************************************
* file name: control.c
* author: 苏尚宇
* date: Mon Feb 13 20:40:50 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/
#include "main.h"
#include "control.h"
#include "display.h"
#include "client.h"

int sockfd;
char quit[10];

char command[][30] = {"AT+LoginUser:", "AT+LoginPasswd:", "AT+LogonUser:",
					 "AT+LogonPasswd:", "AT+ViewFile:", "AT+DownloadPublicFile:",
					 "AT+UploadPublicFile:", "AT+DownloadPrivateFile:", "AT+UploadPrivateFile:",
					 "AT+RemoveUser:", "AT+RemoveFile:", "AT+CheckUser:", "AT+CheckFile:"};

_user end_user;
/*
************************************************************************
* @brief      view_file()
* @param      file_buf: 文件名字
* @return     void
* describe:   查看文件目录
************************************************************************
*/ 
void view_file(char *file_buf)
{
    char buf[50];
	sprintf(buf, "%s%s", command[4], file_buf);
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));
	bzero(file_buf, sizeof(file_buf));
}
/*
************************************************************************
* @brief      down_upload_file()
* @param      i 0：下载共享目录 1：下载个人目录
* @return     void
* describe:   下载文件
************************************************************************
*/ 
void down_upload_file(int i)
{
    char file_buf[10];
    char buf[50];
	printf("请输入需要下载的文件: ");
	scanf("%s", file_buf);
	if (0 == i) {
		sprintf(buf, "%s%s", command[5], file_buf);
	}
	if (1 == i) {
		sprintf(buf, "%s%s", command[7], file_buf);
	}
	write(sockfd, buf, strlen(buf));

	bzero(buf, sizeof(buf));
	bzero(file_buf, sizeof(file_buf));
}
/*
************************************************************************
* @brief      login_user()
* @param      void
* @return     void
* describe:   用户登录
************************************************************************
*/ 
void login_user(void)
{
	char buf[50];
	bzero(buf, sizeof(buf));

	printf("用户名：");
	scanf("%s", end_user.name);
	sprintf(buf, "%s%s", command[0], end_user.name);
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));

	printf("密码：");
	scanf("%s", end_user.passwd);
	sprintf(buf, "%s%s", command[1], end_user.passwd);
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));

	read(sockfd, buf, sizeof(buf));

	if ( !strcmp(buf, "1") ) {
		// view_file();
	}
}
/*
************************************************************************
* @brief      logon_user()
* @param      void
* @return     void
* describe:   用户注册
************************************************************************
*/ 
void logon_user(void)
{
	char buf[50];
	bzero(buf, sizeof(buf));

	printf("用户名：");
	scanf("%s", end_user.name);
	sprintf(buf, "%s%s", command[2], end_user.name);
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));

	printf("密码：");
	scanf("%s", end_user.passwd);
	sprintf(buf, "%s%s", command[3], end_user.passwd);
	write(sockfd, buf, strlen(buf));
	bzero(buf, sizeof(buf));

    printf("注册成功\n");
}
/*
************************************************************************
* @brief      admin_user()
* @param      void
* @return     void
* describe:   管理用户
************************************************************************
*/ 
void admin_user(void)
{
	char user_name[20];
	char buf[50];
	write(sockfd, command[11], strlen(command[11]));
	recv_file_info();
	printf("请输入需要删除的用户: ");
	scanf("%s", user_name);
	strcpy(buf, command[9]);
	strcat(buf, user_name);
	write(sockfd, buf, strlen(buf));
}
/*
************************************************************************
* @brief      admin_file()
* @param      void
* @return     void
* describe:   管理服务器上的文件
************************************************************************
*/ 
void admin_file(void)
{
	char f_buf[10];
	char file_name[20];
	char buf[50];
	char file_buff[20];
	char buff[50];
	char msg[10];

	strcpy(f_buf, command[12]);
	strcat(f_buf, "cloudfile");
	write(sockfd, f_buf, strlen(f_buf));
	recv_file_info();

	printf("请输入要删除的文件: ");
	scanf("%s", file_buff);
	strcpy(buff, command[10]);
	strcat(buff, file_buff);
	write(sockfd, buff, strlen(buff));

	read(sockfd, msg, sizeof(msg));

	if ( !strcmp(msg, "11") ) {
		printf("删除成功\n");
	}
}
/*
************************************************************************
* @brief      exit_enter()
* @param      void
* @return     void
* describe:   回车键退出
************************************************************************
*/  
void exit_enter(void)
{
	printf("----------------------\n");
	printf("\n");
	printf("按回车键退出");
	getchar();
	getchar();
	system("clear");
}
/*
************************************************************************
* @brief      sign_out()
* @param      void
* @return     void
* describe:   客户端退出
************************************************************************
*/  
void sign_out(void)
{
	write(sockfd, "quit", 4);
	strcpy(quit, "quit");
}

