#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
void
find(char *path,char * file){
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if((fd = open(path, 0)) < 0){
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    do{
        if(fstat(fd, &st) < 0){
            fprintf(2, "find: cannot stat %s\n", path);
            break;
        }
        if(st.type!=T_DIR){
            printf("find: '%s': No such file or directory\n",path);
            break;
        }
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf+strlen(buf);
        if(*p!='/'){
            *p++ = '/';
        }
        while(read(fd, &de, sizeof(de)) == sizeof(de)){
            if(de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
                printf("ls: cannot stat %s\n", buf);
                continue;
            }
            if(st.type==T_DIR&&strcmp(de.name,".")&&strcmp(de.name,"..")){
                find(buf,file);
            }
            if(!strcmp(file,de.name)){
                printf("%s\n",buf);
            }
            // printf("%s %d %d %d\n", fmtname(buf), st.type, st.ino, st.size);
        }
    }while(0);
    
    close(fd);
}

int
main(int argc,char*argv[]){
    if(argc<=2){
        printf("find: missing argument\n");
        // find(".",0);
    }
    // else if(argc==2){
    //     find(argv[1],0);
    // }
    else {
        for(int i=2;i<argc;i++){
            find(argv[1],argv[i]);
        }
    }

    exit(0);
}