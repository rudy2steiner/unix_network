//
// Created by root on 18-9-12.
//

#ifndef ANSI_C_TCP_H_H
#define ANSI_C_TCP_H_H
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <signal.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#define SERV_PORT   8080
#define	MAXLINE		4096	/* max text line length */

#define	SA	struct sockaddr
/*
 *  Sigfunc 是一个参数为int 类型，无返回值的函数
 * */
typedef void Sigfunc(int);

/*void (*signal(int,void (*)(int)))(int) simplify to*/

Sigfunc *signal(int signo,Sigfunc *func);
void sig_chld(int signo);

#endif //ANSI_C_TCP_H_H


