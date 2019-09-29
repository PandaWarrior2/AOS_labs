#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char * argv[]){
    if(argc == 1){
        printf("No arguments!\nEnter: %s <filename> <permissions>\n", argv[0]);
    }
    else if(argc == 2){
        printf("No permission options!\n");
    }
    else {
        printf("-----STAGE 1-----\n");
        printf("Creating file %s with permissions %s\n", argv[1], argv[2]);
        int fp = open(argv[1], O_WRONLY | O_CREAT);
        //printf("[SYSCALL] fopen = %d\n", fp);
        if(fp == -1) {
            printf("[SYSCALL] open = -1. File not open. Exit.\n");
            return 0;
        }
        else {
            printf("[SYSCALL] open = %d File open!\n", fp);
        }
        int code;
        char str[255];
        int scode;
        do {
            code = scanf("%s", str);
            if(code != -1){
                scode = write(fp, str, strlen(str));
                printf("[SYSCALL] write = %d\n", scode);
#if (NUM == 6)
                scode = lseek(fp, 1000, SEEK_CUR);
                printf("[NUM 6] Create hole 1000 bytes");
#endif
            }
            else{
                write(fp, EOF, 1);
                printf("EOF\n");
            }

        } while(code != -1);
        int mode = strtol(argv[2],0,8);
        scode = close(fp);
        printf("[SYSCALL] close = %d\n", scode);
        if(chmod(argv[1], mode) < 0){
            perror("chmod error: ");
        }
        printf("-----STAGE 2-----\n");
#ifdef NUM
        fp = open(argv[1], O_RDONLY);
        if(fp == -1) {
            printf("[SYSCALL] open = -1. File not open. Exit.\n");
            return 0;
        }
        else {
            printf("[SYSCALL] open = %d. File open!\n", fp);
        }
    #if (NUM == 2)
        do{
            scode = read(fp, str, 255);
            printf("[SYSCALL] read = %d\n", scode);
            printf("[DATA] str = %s\n", str);
        } while (scode >= 255);
    #elif (NUM >= 4)
        long pos=0;
        printf("NUM = 4\n");
        printf("LSEEK_SET\n");
        pos = lseek(fp,0, SEEK_SET);
        printf("[SYSCALL] Current position = %ld\n", pos);
        scode = read(fp, str, 40);
        printf("[SYSCALL] read = %d\n", scode);
        str[40] = '\0';
        printf("First 40 bytes: %s\n", str);

        printf("LSEEK_CUR\n");
        pos = lseek(fp, -40, SEEK_CUR);
        pos = lseek(fp, 60, SEEK_CUR);
        printf("[SYSCALL] Current position = %ld\n", pos);
        scode = read(fp, str, 40);
        printf("[SYSCALL] read = %d\n", scode);
        if(scode == 0)
            perror("Read error");
        str[scode] = '\0';
        printf("Bytes 60-100: %s\n", str);

    #endif
        close(fp);
#else
        printf("NUM is not defined!");
#endif
        printf("-----STAGE 3-----\n");
        fp = open(argv[1], O_RDWR);
        if(fp == -1) {
            printf("[SYSCALL] open = -1. File not open. Exit.\n");
            return 0;
        }
        else {
            printf("[SYSCALL] open = %d. File open!\n", fp);
        }
        close(fp);
        // dd

    }
    return 1;
}
