/*
 * =====================================================================================
 *
 *       Filename:  n11.c
 *
 *    Description:  Lab 5, number 11
 *
 *        Version:  1.0
 *        Created:  29.10.2019 13:08:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#define DIM 10
int print_matrix(int, int);
int action(int, int);

int main(int argc, char *argv[]){
    int pid;
    int qd;

    if((qd = msgget(IPC_PRIVATE, IPC_CREAT | 0755)) == -1){
        perror("msgget");
        exit(1);
    }

    if((pid = fork()) == -1) {
        perror("fork");
        exit(1);
    }
    int fd;
    if((fd = open("matrix", O_RDWR | O_CREAT, 0755)) == -1){
        perror("open");
        exit(1);
    }
    for(int i = 0; i<DIM*DIM;i++){
        if(write(fd, "0", 1) == -1){
            perror("write");
        }
    }
    struct msg {
        long mtype;
        char mtext[20];
    } msg, ans;

    if(pid){
        print_matrix(fd, DIM*DIM);
    }
    else{
        printf("[C] Дочерний процесс запущен! pid = %d \n", getpid());
    }

}
int print_matrix(int fd, int dim){
    int old_pos;
    if((old_pos = lseek(fd, 0, SEEK_CUR)) == -1){
        perror("[print_matrix] lseek_error");
        return -1;
    }
    if(lseek(fd, 0, SEEK_SET) == -1){
        perror("[print_matrix] lseek error");
        return -1;
    }
    int n;
    char * buf;
    buf = malloc(dim);
    while((n = read(fd,buf,dim))){
        if(n == -1){
            perror("read error");
        }
        else{
            printf("%s\n", buf);
        }
    }
    if(lseek(fd, old_pos, SEEK_SET) == -1){
        perror("[print_matrix] lseek_error");
        return -1;
    }
    return 1;
}

int action(int fd, int dim){
    int old_pos;
    if((old_pos = lseek(fd, 0, SEEK_CUR)) == -1){
        perror("[action] lseek_error");
        return -1;
    }
    if(lseek(fd, 0, SEEK_SET) == -1){
        perror("[action] lseek error");
        return -1;
    }

    char c;
    int n, pos;
    do{
        if((n = read(fd, &c, 1)) == -1){
            perror("read error");
            return -1;
        }
        if(c == '0'){
            if(lseek(fd, (long)-1, SEEK_CUR) == -1){
                perror("lseek error");
            }
            if(write(fd, "1", 1) == -1){
                perror("write error");
            }
            break;
        }
        if((pos = lseek(fd, dim, SEEK_CUR)) == -1){
            perror("lseek error");
        }
        printf("%d ", pos);
        if(pos == 11*dim) break;
    } while(n == 1);
    if(lseek(fd, old_pos, SEEK_SET) == -1){
        perror("[action] lseek_error");
        return -1;
    }
    return pos;
}
