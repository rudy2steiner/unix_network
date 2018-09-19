//
// Created by root on 18-9-16.
//

#include "tcp.h"


Sigfunc *signal(int signo,Sigfunc *func)
{
  struct sigaction act,oact;
    act.sa_handler=func;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    if(signo==SIGALRM){
    #ifdef SA_INTERRUPT
       act.sa_flags|=SA_INTERRUPT;
    #endif
    }else{
    #ifdef SA_RESTART
        act.sa_flags|=SA_RESTART;        /*SunOS 4.x*/
    #endif
    }
    if(sigaction(signo,&act,&oact)<0)
        return (SIG_ERR);
    return (oact.sa_handler);

}
