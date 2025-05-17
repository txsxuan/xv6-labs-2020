#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void do_primes(int prime,int p){
    printf("prime %d\n",prime);
    int fd[2]={-1,-1};
    int next;
    while(!!(read(p,&next,4))){
        if(next!=(next/prime)*prime){
            if(fd[1]<0){
                if(pipe(fd)==-1){
                    fprintf(2, "pipe failed\n");
                    close(p);
                    exit(1);
                }
                if(fork()==0){
                    close(fd[1]);
                    do_primes(next,fd[0]);
                }
                else{
                    close(fd[0]);
                }
            }
            else{
                write(fd[1],&next,4);
            }
        }
    }
    close(p);
    if(fd[1]!=-1){
        close(fd[1]);
        wait((int *) 0);
    }
    exit(0);
}

int
main(){
    int prime=2;
    printf("prime %d\n",prime);
    int fd[2]={-1,-1};
    for(int i=prime+1;i<=35;i++){//由于xv6没有足够多的文件描述符，只能到35为止停止
        if(i!=(i/prime)*prime){
            if(fd[0]==-1){
                if(pipe(fd)==-1){
                    fprintf(2, "pipe failed\n");
                    exit(1);                    
                }
                if(fork()==0){
                    close(fd[1]);
                    do_primes(i,fd[0]);
                }
                else{
                    close(fd[0]);
                }
            }
            else{
                write(fd[1],&i,4);
            }
        }
    }
    if(fd[1]!=-1){
        close(fd[1]);
        wait((int *) 0);
    }
    exit(0);
}
