/*
 * =====================================================================================
 *
 *       Filename:  n4.c
 *
 *    Description:  Lab 4, number 6.
 *
 *        Version:  1.0
 *        Created:  25.10.2019 07:53:20
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
#include <errno.h>
#include <unistd.h>
#include <string.h>
//#define check(func, name) func == -1 ? perror(name) : func
struct packet{
    int id;
    int value;
};
int main(int argc, char * argv []){
    /*
        fds[0] - чтение
        fds[1] - запись
    */
    int fds[2], fds_i[2];
    int pid;
    if(pipe(fds) == -1){
        perror("pipe error");
    }
    if(pipe(fds_i) == -1){
        perror("pipe error");
    }
    if((pid = fork()) == -1){
        perror("fork error");
    }

    if(pid){
        printf("[P] Дочерний процесс создан! PID = %d\n", pid);
        close(fds[0]);
        close(fds_i[1]);
        close(0);
        dup2(fds[1], 0);
        struct packet t;
        int id = 0;
        char *c;
        t.value = rand() % 10000;
        t.id = id++;
        if(write(fds[1], &t, sizeof(struct packet)) == -1){
           perror("[P] write error");
        }
        else{
            printf("\n[P] Пакет сгенерирован и отправлен! (ID = %d ; VALUE = %d)\n", t.id, t.value);
        }
        wait(NULL);
        int n;
        do{
            if((n = read(fds_i[0], &c, 1)) == -1){
                perror("[P] read error!");
            }
            else{
                if(write(1, &c, 1) == -1){
                    perror("[P] write error");
                }
                write(1,".",1);
            }
        }while(n == 1);

        printf("[P] Ответ получен!\n");
        printf("[P] Завершение родительского процесса!\n");
        if(close(fds[1]) == -1){
            printf("[P] close fds[1] error");
        }
        if(close(fds_i[0]) == -1){
            printf("[P] close fds_i[0] error");
        }
    }
    else{
        printf("[C] Child process started!");
        close(fds[1]);
        close(fds_i[0]);
        struct packet rec;
        char buf[100];
        close(1);
        dup2(fds_i[1], 1);
        execve("n4sub", 0, NULL);
        perror("execve error");

    }
}

