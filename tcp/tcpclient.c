//
// Created by root on 18-9-12.
//

#include "tcp.h"
#include "read.h"

void str_cli(FILE *fd,int sockfd){
    char sendline[MAXLINE],recvline[MAXLINE];
    while(fgets(sendline,MAXLINE,fd)!=NULL){
         write(sockfd,sendline,strlen(sendline));
         if(readline(sockfd,recvline,MAXLINE)==0){
             printf("str_cli:server terminated prematurely");
             exit(1);
         }
        fputs(recvline,stdout);
    }
}

/**
 * 观察网络连接
 * netstat -tunlpa|grep -E 'tcpc|tcps'
 *
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
    str_cli(stdin,sockfd);
    exit(0);
}


