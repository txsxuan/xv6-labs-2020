#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
int
main(int argc,char*argv[]){
    if(argc<2){
        printf("xargs: missing argument\n");
        exit(1);
    }
    char buf[512];
    char *p=buf;
    while((p-buf<511)&&read(0,p,1)){
        if(*p=='\n'){
            *p++=0;
            if(fork()==0){
                char *args[argc+1];
                for(int i=1;i<argc;i++){
                    args[i-1]=argv[i];
                }
                args[argc-1]=buf;
                args[argc]=0;
                exec(argv[1],args);
                exit(0);
            }
            else{
                wait((int *)0);
                p=buf;
            }
        }
        else{
            p++;
        }
    }
    exit(0);
}