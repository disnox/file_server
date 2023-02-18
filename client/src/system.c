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
#include "system.h"
/*
************************************************************************
* @brief      system_control()
* @param      void
* @return     void
* describe:   总控制台
************************************************************************
*/ 
void system_control(void)
{
    int opt1, opt2, opt3, opt4;
	char buf[10] = "public";

    display_system();
    scanf("%d", &opt1);
    switch (opt1) {
        case 1:
            login_user();
            while (1) {
                display_order();
                scanf("%d", &opt2);
                switch (opt2) {
                    case 1:
                        view_file(buf);
						recv_file_info();
                        while (1) {
                            display_choice_file();
                            scanf("%d", &opt3);
                            switch (opt3) {
                                case 1:
                                    // TODO: 处理选择 1 的操作
									down_upload_file(0);
									recv_files();
                                    exit_enter();
                                    break;
                                case 2:
                                    // TODO: 处理选择 2 的操作
                                    send_files(0);
                                    exit_enter();
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("无效的选择，请重新选择\n");
                                    break;
                            }
                            if (opt3 == 0) {
                                break;
                            }
                        }
                        break;
                    case 2:
						view_file(end_user.name);
                        recv_file_info();
                        while (1) {
                            display_choice_file();
                            scanf("%d", &opt3);
                            switch (opt3) {
                                case 1:
                                    // TODO: 处理选择 1 的操作
									down_upload_file(1);
									recv_files();
                                    exit_enter();
                                    break;
                                case 2:
                                    // TODO: 处理选择 2 的操作
                                    send_files(1);
                                    exit_enter();
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("无效的选择，请重新选择\n");
                                    break;
                            }
                            if (opt3 == 0) {
                                break;
                            }
                        }
                        break;
                    
                    case 3:
                        sign_out();
                        break;
                    case 0:
                        break;
                    default:
                        printf("无效的选择，请重新选择\n");
                        break;
                }
                if (opt2 == 0) {
                    break;
                }
            }
            break;
        case 2:
            // TODO: 处理选择 2 的操作
            logon_user();
            exit_enter();
            break;
        case 3:
            while(1) {
                display_admin();
                scanf("%d", &opt4);
                switch (opt4) {
                    case 1:
                        admin_user();
                        exit_enter();
                        break;
                    case 2:
                        admin_file();
                        exit_enter();
                        break;
                    case 0:
                        break;
                    default:
                        printf("无效的选择，请重新选择\n");
                        break;
                }
                if (opt4 == 0) {
                    break;
                }
            }
            break;
        case 4:
            sign_out();
            break;
        default:
            printf("无效的选择，请重新选择\n");
            break;
    }
}

