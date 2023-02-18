<h2 align="center">
📂文件服务器
</h2><br>
<pre align="center">
 Build with 📷<a href="https://disnox.top">disnox</a> 
</pre>



<p align="center">
<br>
<a href="https://www.disnox.top/project">🖥 More Items</a>
<br>
<a href=" " rel="nofollow"><img src="https://img.shields.io/badge/-%F0%9F%92%BBLinux-blue"></a>
<a href=" " rel="nofollow"><img src="https://img.shields.io/badge/-%F0%9F%91%A8%E2%80%8D%F0%9F%92%BBC%2FC%2B%2B-blue"></a>
<a href=" " rel="nofollow"><img src="https://img.shields.io/badge/-%F0%9F%93%9Aproject-blue"></a>
</p>


## 1. 项目简介

该项目是一个基于Linux网络编程的文件服务器，可以提供文件上传、下载、删除等功能。用户可以通过客户端与服务器进行交互，实现对文件的管理。

## 2. 软件环境

+ **Makefile** 工程管理
+ **VsCode** 代码编辑器
+ **Ubuntu22.04 Linux** 子系统

## 3. 项目架构

+ 服务器端使用C语言编写，采用多线程/多进程模型，支持多用户同时访问
+ 客户端使用C语言编写，与服务器端通过TCP/IP协议进行通信
+ 服务器与客户端的通信采用自定义报文数据进行交互，指令格式如下：

```C
char msg[100] = "AT+LoginUser:disnox";	// 数据格式
```

| 报文指令         | 数据头  | 消息类型                | 分隔符 | 数据消息          |
| ---------------- | ------- | ----------------------- | ------ | ----------------- |
| **用户验证**     | **AT+** | **LoginUser**           | **:**  | **用户名字**      |
| **密码验证**     | **AT+** | **LoginPasswd**         | **:**  | **密码**          |
| **用户注册**     | **AT+** | **LogonUser**           | **:**  | **用户名字**      |
| **密码注册**     | **AT+** | **LogonPasswd**         | **:**  | **密码**          |
| **查看文件**     | **AT+** | **ViewFile**            | **:**  | **文件名字**      |
| **下载共享文件** | **AT+** | **DownloadPublicFile**  | **:**  | **文件名字**      |
| **上传共享文件** | **AT+** | **UploadPublicFile**    | **:**  | **文件名字**      |
| **下载私人文件** | **AT+** | **DownloadPrivateFile** | **:**  | **文件名字**      |
| **上传私人文件** | **AT+** | **UploadPrivateFile**   | **:**  | **文件名字**      |
| **查看用户**     | **AT+** | **CheckUser**           | **:**  | **NULL**          |
| **查看文件**     | **AT+** | **CheckFile**           | **:**  | **File/文件名字** |
| **删除用户**     | **AT+** | **RemoveUser**          | **:**  | **用户名字**      |
| **删除文件**     | **AT+** | **RemoveFile**          | **:**  | **文件名字**      |

+ 客户端发送指令给服务器解析进行相应操作，留有足够的扩展性为以后添加新功能和特性提供便利。

## 4. 项目实现功能

+ 实现文件的上传、下载、删除等基本操作；

+ 支持多用户同时访问服务器；

+ 实现安全的用户身份验证机制，防止非法访问；

+ 实现文件上传时的断点续传功能，提高文件上传效率；

+ 实现基于目录的权限控制，确保用户只能访问其有权限的文件；

+ 实现可扩展性，支持添加新的功能和特性。

## 5. 目录结构描述

```bash
.
├── bin
│   ├── client				# 服务器可执行文件
│   └── server				# 客户端可执行文件
├── client					# 客户端程序文件
│   ├── inc					# 存放.h文件
│   │   ├── client.h
│   │   ├── control.h
│   │   ├── display.h
│   │   ├── main.h
│   │   ├── system.h
│   │   └── thread.h
│   ├── lib					# 存放库文件
│   ├── obj					# 存放.o文件
│   └── src					# 存放.c文件
│       ├── client.c		# 客户端执行
│       ├── control.c		# 系统控制函数
│       ├── display.c		# 菜单显示函数
│       ├── main.c			# 主函数
│       ├── system.c		# 总控制台
│       └── thread.c		# 线程函数
├── cloudfile				# 保存文件目录
│   └──  public				# 公共文件
│       ├── 1.bmp
│       └── 9.bmp
├── doc						# 存放信息文件
│   ├── 1.xls				
│   └── user.txt
├── server					# 服务器程序文件
│   ├── inc					# 存放.h文件
│   │   ├── control.h
│   │   ├── kernel_list.h
│   │   ├── main.h
│   │   ├── serve.h
│   │   ├── thread.h
│   │   └── user_info.h
│   ├── lib					# 存放库文件
│   ├── obj					# 存放.o文件
│   └── src					# 存放.c文件
│       ├── control.c		# 总控制文件
│       ├── main.c			# 主函数
│       ├── serve.c			# 服务器执行函数
│       ├── thread.c		# 线程函数
│       └── user_info.c		# 信息管理内核链表
├── Makefile				# Makefile工程配置文件
├── README.md				# README
└── 文件服务器.xmind			 # 文件服务器思维导图
```
