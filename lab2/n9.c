/*
 * =====================================================================================
 *
 *       Filename:  n9.c
 *
 *    Description:  Lab #2, Number 9.
 *
 *        Version:  1.0
 *        Created:  09.10.2019 12:35:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
int copy(int, int);
int main(int argc, char * argv[]){
    if(argc == 1){
        printf("Usage: %s filename\n", argv[0]);
    }
    else {

        /*if((fp = open(argv[1], O_RDONLY)) == -1){
            perror("");
            exit(1);
        }*/
        //else{
        int pid;
        if((pid = fork()) == -1){
            perror("");
            exit(2);
        }
        else if (pid){
            printf("[P] Parent PID = %d\n", getpid());
            int fpp, fd_p;
            if((fpp = open(argv[1], O_RDONLY)) == -1) {
                perror("[P] Open error");
                exit(10);
            }
            if((fd_p = open("out_parent", O_RDWR | O_CREAT, 0755)) == -1){
                perror("[P] open out_parent error");
                exit(3);
            }
            else {
                if(copy(fpp, fd_p)){
                    printf("[P] Файл out_parent записан! выводим его на экран!\n");
                    lseek(fd_p, 0, SEEK_SET);
                    int code;
                    if(wait(&code) == -1) {
                        perror("[P] wait error");
                        exit(4);
                    }
                    else{
                        printf("[P] Дочерний процесс завершён!\n");
                        printf("[P] ----Start out_parent----\n");
                        copy(fd_p, 1);
                        printf("[P] ----END out_parent----\n");
                        int fd_c = open("out_child", O_RDONLY);
                        printf("[P] ----Start out_child----\n");
                        copy(fd_c, 1);
                        printf("[P] ----END out_child----\n");
                        close(fd_c);
                    }
                }
                close(fd_p);
            }
            close(fpp);
        }
        else {
            printf("[C] Child process started! PID = %d\n", getpid());
            int fpc, fd_c;
            if((fpc = open(argv[1], O_RDONLY)) == -1) {
                perror("[C] Open error");
                exit(10);
            }
            if((fd_c = open("out_child", O_RDWR | O_CREAT, 0755)) == 1){
                perror("[C] open out_child error");
                exit(4);
            }
            else {
                if(copy(fpc, fd_c)){
                    printf("[C] файл out_child записан!\n");
                    printf("[C] ----START out_child----\n");
                    lseek(fd_c, 0, SEEK_SET);
                    copy(fd_c, 1);
                    printf("[C] ----END out_child----\n");

                    int fd_p = open("out_parent", O_RDONLY);
                    printf("[P] ----Start out_parent----\n");
                    copy(fd_p, 1);
                    printf("[P] ----END out_parent----\n");
                    close(fd_p);
                }
                close(fd_c);
            }
            close(fpc);

        }
        //}
    }
    return 0;
}

int copy(int from, int to){
    int c;
    char buf[255];
    do{
        if((c = read(from, buf, 255)) == -1){
            printf("Read error (PID = %d): %s\n", getpid(),sys_errlist[errno]);
            return 0;
        }

        if(write(to, buf, c) == -1){
            printf("Write error (PID = %d): %s\n", getpid(), sys_errlist[errno]);
            return 0;
        }
    } while(c == 255);
    return 1;
}

