//
// Created by root on 18-10-4.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define GN_NONNEG       01      /* Value must be >= 0 */
#define GN_GT_0         02      /* Value must be > 0 */

/* By default, integers are decimal */
#define GN_ANY_BASE   0100      /* Can use any base - like strtol(3) */
#define GN_BASE_8     0200      /* Value is expressed in octal */
#define GN_BASE_16    0400      /* Value is expressed in hexadecimal */

static int glob=0;
static pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
/**
 * cc thread.c -pthread -o thread
 **/
static void *  threadFunc(void *arg){
    int loops= *((int *)arg);
    int loc,j,s;
    for(j=0;j<loops;j++){
        s=pthread_mutex_lock(&mtx);
        if(s!=0){
            printf(" thread mutex lock failed!");
            exit(1);
        }
        loc=glob;
        loc++;
        glob=loc;
        s=pthread_mutex_unlock(&mtx);
        if(s!=0){
            printf(" thread mutex unlock failed!");
            exit(1);
        }
    }
}

int getInt(const char *arg, int flags, const char *name){

    char *endptr;
    int base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 :
                                       (flags & GN_BASE_16) ? 16 : 10;
    long g = strtol(arg, &endptr, base);
    return (int)g;
}

int main(int argc,char *argv[]){
    pthread_t t1,t2;
    int loops,s;
    loops=(argc>1)?getInt(argv[1],GN_GT_0,"num_loops"):10000000;
    printf("loops init:%d \n",loops);
    s=pthread_create(&t1,NULL,threadFunc,&loops);
    if(s!=0){
        printf("create thread failed!");
        exit(1);
    }
    s=pthread_create(&t2,NULL,threadFunc,&loops);
    if(s!=0){
        printf("create thread failed!");
        exit(1);
    }
    s=pthread_join(t1,NULL);
    if(s!=0){
        printf("join thread failed!");
        exit(1);
    }
    s=pthread_join(t2,NULL);
    if(s!=0){
        printf("join thread failed!");
        exit(1);
    }
    printf("glob=%d \n",glob);
    exit(EXIT_SUCCESS);
}





