//
// Created by root on 18-9-16.
//

#include "tcp.h"

/* to avoid zombie */

void sig_chld(int signo){
    pid_t pid;
    int stat;
    while((pid=waitpid(-1,&stat,WNOHANG))>0)
        printf("child %d terminated\n",pid);
    return;
}