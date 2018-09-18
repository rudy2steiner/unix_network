//
// Created by root on 18-9-11.
//

#include "tcp.h"
#define	LISTENQ		1024	/* 2nd argument to listen() */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */


void str_echo(int socketfd){
    ssize_t n;
    char buf[MAXLINE];
 again:
    while((n=read(socketfd,buf,MAXLINE))>0){
        write(socketfd,buf,n);
    if(n<0&&errno==EINTR)
        goto again;
    else if(n<0){
        printf("str_echo: read error \n");
        exit(1);
    }
   }
}

int main(int argc,char **argv)
{
    int listenfd,connfd;
    pid_t  childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(SERV_PORT);
    bind(listenfd,(SA *)&servaddr, sizeof(servaddr));
    listen(listenfd,LISTENQ);
    printf("start to listen at port %d \n",SERV_PORT);
    // process child process close
    signal(SIGCHLD,sig_chld);
    for(;;){
        clilen= sizeof(cliaddr);
        if((connfd=accept(listenfd,(SA *)&cliaddr,&clilen))<0){
            // process interrupt
           if(errno==EINTR)
               continue;
            else
               printf("accept error");
        }else {
            if ((childpid = fork()) == 0) { /*child process*/
                close(listenfd);
                str_echo(connfd);
                exit(0);
            }
            close(connfd);
        }
    }
}


