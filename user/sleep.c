#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc,char *argv[])
{
    int sleeptime;
    if(argc <= 1 || argc>2) {
        printf("usage: sleep time\n");
        exit(1);
    }
    sleeptime=atoi(argv[1]);
    printf("sleep time = %s\n",argv[1]);
    sleep(sleeptime);
    exit(0);
}