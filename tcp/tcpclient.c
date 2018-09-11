//
// Created by root on 18-9-12.
//
#include <stdio.h>
#include <sys/socket.h>
#include "tcp.h"

static int	read_cnt;
static char	*read_ptr;
static char	read_buf[MAXLINE];

static ssize_t
my_read(int fd, char *ptr)
{

    if (read_cnt <= 0) {
        again:
        if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return(-1);
        } else if (read_cnt == 0)
            return(0);
        read_ptr = read_buf;
    }

    read_cnt--;
    *ptr = *read_ptr++;
    return(1);
}

ssize_t
readline(int fd, void *vptr, size_t maxlen)
{
    ssize_t	n, rc;
    char	c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c == '\n')
                break;	/* newline is stored, like fgets() */
        } else if (rc == 0) {
            *ptr = 0;
            return(n - 1);	/* EOF, n - 1 bytes were read */
        } else
            return(-1);		/* error, errno set by read() */
    }

    *ptr = 0;	/* null terminate like fgets() */
    return(n);
}

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


