//
// Created by root on 18-9-22.
// cc   -I ..  nioserv.c
// -I 指定头文件搜索路径
//

#include "tcp/tcp.h"
#define	LISTENQ		1024	/* 2nd argument to listen() */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

int main(int argc,char **argv)
{
    int i,maxi,maxfd,listenfd,connfd,sockfd;
    int nready,client[FD_SETSIZE]; //FD_SETSIZE upper limit
    ssize_t n;
    fd_set rset,allset;
    char buf[MAXLINE];
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
    maxfd=listenfd;
    maxi=-1;
    for(i=0;i<FD_SETSIZE;i++){
        client[i]=-1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd,&allset);

    // process child process close
    //signal(SIGCHLD,sig_chld);
    for(;;){
        rset=allset;
        // rset is value-result arguments
        nready=select(maxfd+1,&rset,NULL,NULL,NULL);
        if(FD_ISSET(listenfd,&rset)){ // new client connection
            clilen= sizeof(cliaddr);
            if((connfd=accept(listenfd,(SA *)&cliaddr,&clilen))<0){
                // process interrupt
//                if(errno==EINTR)
//                    continue;
//                else {
                    printf("accept error");
                    close(connfd);
//                }
            }
            for(i=0;i<FD_SETSIZE;i++){
                if(client[i]<0){
                    client[i]=connfd;
                    break;
                }
            }
            if(i==FD_SETSIZE){
                printf("too many connections!");
                //close(client[i]);
            }
            FD_SET(connfd,&allset);
            if(connfd>maxfd){
                maxfd=connfd;
            }
            if(i>maxi){
                maxi=i;
            }
            if(--nready<=0)
                continue;    //no more readable client
        }
        for(i=0;i<=maxi;i++){
            if((sockfd=client[i])<0)
                continue;
            if(FD_ISSET(sockfd,&rset)){
                if((n=read(sockfd,buf,MAXLINE))==0){
                    close(sockfd);
                    FD_CLR(sockfd,&allset);
                    client[i]=-1;
                }else{
                    write(sockfd,buf,n);
                }
                if(--nready<=0)
                    break;
            }
        }
    }
}
