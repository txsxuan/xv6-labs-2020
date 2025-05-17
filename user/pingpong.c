#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(){
    int p[2];
    if(!!(pipe(p))){
        printf("pipe allocate failed !\n");
        exit(1);
    }
    if(fork() == 0) {
        char buf[1];
        read(p[0],buf,1);
        close(p[0]);
        printf("%d : received ping\n",getpid());
        write(p[1],buf,1);
        close(p[1]);
        exit(0);
    }
    else{
        // close(p[0]);
        char buf[1];
        write(p[1],"a\n",1);
        close(p[1]);
        // sleep(1);
        wait((int *)0);
        read(p[0],buf,1);
        close(p[0]);
        printf("%d : received pong\n",getpid());
    }
    exit(0);
}