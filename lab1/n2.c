#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
int main(int argc, char * argv[]){
    if(argc == 1){
        printf("No arguments!\n");
    }
    else if(argc == 2){
        printf("No permission options!\n");
    }
    else {
        printf("-----STAGE 1-----\n");
        printf("Creating file %s with permissions %s\n", argv[1], argv[2]);
        FILE *fp = fopen(argv[1], "w");
        //printf("[SYSCALL] fopen = %d\n", fp);
        if(!fp) {
            printf("[SYSCALL] fopen = 0. File not open. Exit.\n");
            return 0;
        }
        else {
            printf("[SYSCALL] fopen != 0. File open!\n");
        }
        int code;
        char str[255];
        int scode;
        do {
            code = scanf("%s", str);
            if(code != -1){
                fwrite(&str, sizeof(char), strlen(str), fp);
                scode = fwrite("\n", sizeof(char), 1, fp);
                printf("[SYSCALL] fwrite = %d\n", scode);
            }

        } while(code != -1);
        int mode = strtol(argv[2],0,8);
        scode = fclose(fp);
        printf("[SYSCALL] fclose = %d\n", scode);
        if(chmod(argv[1], mode) < 0){
            perror("chmod error: ");
        }

        printf("-----STAGE 2-----\n");
        fp = fopen(argv[1], "r");
        if(!fp) {
            printf("[SYSCALL] fopen = 0. File not open. Exit.\n");
            return 0;
        }
        else {
            printf("[SYSCALL] fopen != 0. File open!\n");
        }
        scode = fread(str, sizeof(char), 1, fp);
        printf("[SYSCALL] fread = %d\n", scode);

    }
    return 1;
}
