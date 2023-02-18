/*
************************************************************************
* file name: control.c
* author: 苏尚宇
* date: Tue Feb 14 21:20:21 CST 2023
* path: /mnt/e/Code/puresoft/project/server
* describe: NULL
************************************************************************
*/

#include "main.h"
#include "thread.h"
#include "control.h"
#include "serve.h"
#include "user_info.h"

/*
************************************************************************
* @brief      view_file()
* @param      timestamp: 时间戳  timebuf: 时间
* @return     void
* describe:   时间戳转换为时分秒的格式
************************************************************************
*/ 
void convert_timestamp_to_time(long int timestamp, char *timebuf) 
{
    // 创建一个time_t类型的时间戳
    time_t rawtime = (time_t)timestamp;
    
    // 创建一个tm结构体来存储时分秒的值
    struct tm *timeinfo;
    
    // 调用localtime函数，将time_t时间戳转换为本地时间，存储在tm结构体中
    timeinfo = localtime(&rawtime);
    
    // 从tm结构体中获取时分秒的值，并保存在timebuf中
    sprintf(timebuf, "%02d:%02d:%02d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}
/*
************************************************************************
* @brief      mkdir_user()
* @param      data: 文件名
* @return     void
* describe:   注册时创建用户个人目录
************************************************************************
*/ 
void mkdir_user(char *data)
{
    char dirname[50];  // 为防止路径超长，将数组长度调大
    bzero(dirname, sizeof(dirname));
    sprintf(dirname, "cloudfile/%s", data);
    printf("%s\n", dirname);
    // 创建 "temp" 子目录
    int ret = mkdir(dirname, 0777);
    if (ret != 0) {
        perror("mkdir() fail");
        exit(1);
    }
}
/*
************************************************************************
* @brief      view_file()
* @param      data: 文件名  confd: 通信套接字
* @return     void
* describe:   发送文件
************************************************************************
*/ 
void view_file(int *confd, char *data)
{
	// 打开目录
	int i = 0;
	char buf[1024], atime[10], mtime[10];
    char dirname[50];  // 为防止路径超长，将数组长度调大

    bzero(dirname, sizeof(dirname));
    sprintf(dirname, "cloudfile/%s", data);
    printf("%s\n", dirname);

    // DIR *dp = opendir("cloudfile/disnox");
    DIR *dp = opendir(dirname);
    if (dp == NULL) {
        perror("opendir() fail");
        exit(1);
    }

    // chdir("cloudfile/disnox");
	chdir(dirname);
    // 读取目录文件
    struct dirent *d;
	struct stat file_stat;

	write(*confd, "Name  	Size  		Permissions  	Last accessed  	Last modified", 58);
    while ((d = readdir(dp)) != NULL) {
        // 打印目录文件名
		i++;
		if (i > 2) {
			// 获取文件信息
			if (stat(d->d_name, &file_stat) == -1) {
				perror("stat() fail");
				exit(1);
			}
			// 时间戳转换为时分秒
			convert_timestamp_to_time(file_stat.st_atime, atime);
			convert_timestamp_to_time(file_stat.st_mtime, mtime);
			// 打印文件信息
			sprintf(buf, "%-8s%-7lld bytes	%-16o%-10s	%-10s", d->d_name, (long long)file_stat.st_size, \
			file_stat.st_mode & 0777, atime, mtime);
			printf("%s\n", buf);
			write(*confd, buf, strlen(buf));
		}
    }
    // 关闭目录
	write(*confd, "2", 2);

	chdir("../../");
    closedir(dp);
}
/*
************************************************************************
* @brief      connect_serve_init()
* @param      data: 文件名  file: 保存到的文件路径
* @return     void
* describe:   发送文件
************************************************************************
*/ 
void send_files(char *data, char *file)
{
    //1. 先发送文件的大小和文件的名字
	struct filestat info;
	struct stat buf;

    bzero(info.name, sizeof(info.name));
    sprintf(info.name, "cloudfile/%s/%s", file, data);
    printf("%s\n", info.name);
	
	//判断文件是否存在
	if(access(info.name, F_OK))
	{
		printf("文件不存在, 请再次输入\n");
		// ....
	}
	stat(info.name, &buf);
	info.size = buf.st_size;
	printf("%s: %d\n", info.name, info.size);
	
	//发送已经获取到的文件的名字和大小
	write(confd, &info, sizeof(info));

	//2. 发送文件的数据
	int fd = open(info.name, O_RDONLY);
	
	char msg[1024*1024];
	int nread;
	while(1)
	{
		nread = read(fd, msg, 1024*1024);
		printf("nread: %d\n", nread);
		if(nread == 0) {
			break;
		}
		write(confd, msg, nread);
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
void recv_files(char *data, char *file)
{
	// 1. 接收文件的名字和大小
	struct filestat info;
	
	read(confd, &info, sizeof(info));
	printf("%s: %d\n", info.name, info.size);
    sprintf(info.name, "cloudfile/%s/%s", file, data);
    printf("%s: %d\n", info.name, info.size);

	printf("---------------------\n");

	// 2. 接收文件内容
	int nread, total = 0;
	char msg[1024];
	int fd = open(info.name, O_CREAT | O_WRONLY, 0666);
	
	while(1)
	{
		nread = read(confd, msg, 1024);
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
* @brief      send_user_list()
* @param      void
* @return     void
* describe:   发送用户信息
************************************************************************
*/ 
void send_user_list(void)
{
	struct list_head *pos;
	kernel_list_node *item;
	char buf[50];

	list_for_each(pos, &user_list)
	{
		item = list_entry(pos, kernel_list_node, point_node);
		printf("%s\n", item->user_info.name);
		write(confd, item->user_info.name, strlen(item->user_info.name));
	}
	write(confd, "!", 2);
}
/*
************************************************************************
* @brief      delete_user()
* @param      void
* @return     void
* describe:   删除用户信息
************************************************************************
*/ 
void delete_user(char *data)
{
	char buf[50];
	delete_user_item(data);
	traverse_user_list();
	save_user_to_file("doc/user.txt");
	sprintf(buf, "cloudfile/%s", data);
	delete_directory(buf);
}
/*
************************************************************************
* @brief      delete_directory()
* @param      void
* @return     void
* describe:   删除用户目录
************************************************************************
*/ 
int delete_directory(const char* dir_path) 
{
    DIR* dir = opendir(dir_path);
    if (dir == NULL) {
        perror("Error");
        return -1;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            // 如果是目录，则递归删除目录
            delete_directory(path);
        } else {
            // 如果是文件，则删除文件
            if (unlink(path) != 0) {
                perror("Error");
                return -1;
            }
        }
    }

    closedir(dir);

    // 删除空目录
    if (rmdir(dir_path) != 0) {
        perror("Error");
        return -1;
    }

    return 0;
}
/*
************************************************************************
* @brief      delete_file()
* @param      void
* @return     void
* describe:   删除用户信息
************************************************************************
*/ 
int delete_file(const char *file_path) 
{
    int status = remove(file_path);

    if (status != 0) {
        fprintf(stderr, "Error: Unable to delete the file %s\n", file_path);
        return 1;
    }
	write(confd, "11", 2);
    return 0;
}
/*
************************************************************************
* @brief      print_directory_contents()
* @param      path: 文件名字
* @return     void
* describe:   发送所有文件
************************************************************************
*/ 
void print_directory_contents(const char *path)
{
	static int a = 0;

    struct dirent *dp;
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Error");
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;

        char file_path[1024];
        snprintf(file_path, sizeof(file_path), "%s/%s", path, dp->d_name);

        struct stat statbuf;
        if (stat(file_path, &statbuf) == -1)
            continue;

        if (S_ISDIR(statbuf.st_mode)) {
            char dir_path[1024];
            sprintf(dir_path, "%s", file_path);
            write(confd, dir_path, strlen(dir_path));
            print_directory_contents(file_path);
        } else {
            write(confd, file_path, strlen(file_path));
        }
    }
	a++;
	if (2 == a) {
		a = 0;
		write(confd, "********************************************", 45);
	}
    closedir(dir);
}






