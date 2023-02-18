/*
************************************************************************
* file name: client/src/client.c
* author: 苏尚宇
* date: Sun Feb 12 15:53:42 CST 2023
* path: /mnt/e/Code/puresoft/project
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "client.h"
#include "control.h"
#include "display.h"
/*
************************************************************************
* @brief      connect_serve_init()
* @param      void
* @return     void
* describe:   连接服务器
************************************************************************
*/ 
void connect_serve_init(void)
{
	// 1. 获取一个流式套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		fprintf(stderr, "socket() fail: %s\n", strerror(errno));
		exit(0);
	}
	
	// 3. 连接服务器
	struct sockaddr_in saddr;
	saddr.sin_family = AF_INET;	//ipv4
	saddr.sin_port = htons(50000);	//端口
	saddr.sin_addr.s_addr = inet_addr("192.168.1.93");	//服务器的ip地址
	if ( connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1 ) {
		fprintf(stderr, "connect() fail: %s\n", strerror(errno));
		exit(0);
	}
	printf("连接成功\n");
} 
/*
************************************************************************
* @brief      recv_file_info()
* @param      void
* @return     void
* describe:   接收文件信息
************************************************************************
*/ 
void recv_file_info(void)
{
    char file_buf[100];
    while (1) {
        bzero(file_buf, sizeof(file_buf));
        int nread = read(sockfd, file_buf, 100);
        if (nread > 2) {
            printf("%s\n", file_buf);
        }

		if ( !strcmp(file_buf, "!") ) {
			break;
		}
		if ( !strcmp(file_buf, "********************************************") ) {
			break;
		}
    }
}
/*
************************************************************************
* @brief      recv_files()
* @param      void
* @return     void
* describe:   接收文件数据
************************************************************************
*/ 
void recv_files(void)
{
	// 1. 接收文件的名字和大小
	struct filestat info;
	
	read(sockfd, &info, sizeof(info));
	printf("%s: %d\n", info.name, info.size);
	printf("%s: %d\n", rindex(info.name, '/')+1, info.size);
	char *pname = rindex(info.name, '/')+1;

	printf("---------------------\n");

	// 2. 接收文件内容
	int nread, total = 0;
	char msg[1024];
	int fd = open(pname, O_CREAT | O_WRONLY, 0666);
	
	while(1)
	{
		nread = read(sockfd, msg, 1024);
		write(fd, msg, nread);	//从套接字中读到多少字节，就写多字节
		//如果读到的字节总数都已经等于文件的大小，那么文件内容已经接收完毕
		total += nread;
		if(total == info.size)
			break;	
	}
	printf("下载完成\n");
}
/*
************************************************************************
* @brief      connect_serve_init()
* @param      i 0: 发送到公共目录 1: 发送到个人目录
* @return     void
* describe:   发送文件
************************************************************************
*/ 
void send_files(int i)
{
	//1. 先发送文件的大小和文件的名字
	struct filestat info;
	struct stat buf;
	char buff[80];

	printf("请输入要发送的文件名字: ");
	scanf("%s", info.name);
	printf("---------info.name: %s\n", info.name);
	//判断文件是否存在
	if(access(info.name, F_OK)) {
		printf("文件不存在, 请再次输入\n");
		// ....
	}
	// 发送指令+文件名字
	if (0 == i) {
		sprintf(buff, "%s%s", command[6], info.name);
		printf("---------buff: %s\n", buff);
	}
	if (1 == i) {
		sprintf(buff, "%s%s", command[8], info.name);
		printf("---------buff: %s\n", buff);
	}
	write(sockfd, buff, strlen(buff));

	stat(info.name, &buf);
	info.size = buf.st_size;
	printf("%s: %d\n", info.name, info.size);
	
	//发送已经获取到的文件的名字和大小
	write(sockfd, &info, sizeof(info));


	//2. 发送文件的数据
	int fd = open(info.name, O_RDONLY);
	
	char msg[1024*1024];
	int nread;
	while(1)
	{
		nread = read(fd, msg, 1024*1024);
		if(nread == 0) {
			break;
		}
		write(sockfd, msg, nread);
	}
	printf("上传完成\n");
}

