//
// Created by root on 18-9-19.
//

#include "tcp/tcp.h"
#include "tcp/read.h"
#include <math.h>

int max(int a,int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

/**
 * select 多个文件描述符
 **/


void nio_cli(FILE *fd,int sockfd){

    char sendline[MAXLINE],recvline[MAXLINE];
    int maxfdp1;
    int stdineof=0;
    fd_set rset;
    for(;;){
        if(stdineof==0)
            FD_SET(fileno(fd),&rset);
        FD_SET(sockfd,&rset);
        maxfdp1=max(fileno(fd),sockfd)+1;
        select(maxfdp1,&rset,NULL,NULL,NULL);
        if(FD_ISSET(sockfd,&rset)){
            if(readline(sockfd,recvline,MAXLINE)==0){
                if(stdineof==1){
                    return;
                }else {
                    printf("str_cli:server terminated prematurely");
                    exit(1);
                }
            }
            fputs(recvline,stdout);
        }
        if(FD_ISSET(fileno(fd),&rset)){
            if(fgets(sendline,MAXLINE,fd)!=NULL){
                write(sockfd,sendline,strlen(sendline));
            }else{
                //exit
                stdineof=1;
                shutdown(sockfd,SHUT_WR);
                FD_CLR(fileno(fd),&rset);
                continue;
            }
        }
    }

}


/**
 *  观察网络连接
 *  netstat -tunlpa|grep -E 'tcpc|tcps'
 *  cc ../tcp/read.c nioclient.c -o nioclient.o
 **/

int main(int argc,char **argv){

    int sockfd;
    struct sockaddr_in servaddr;
    if(argc!=2) {
        printf("error: arguments is less than 2");
        exit(1);
    }
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(SERV_PORT);
    inet_pton(AF_INET,argv[1],&servaddr.sin_addr);
    connect(sockfd,(SA *) &servaddr, sizeof(servaddr));
    nio_cli(stdin,sockfd);
    exit(0);
}

