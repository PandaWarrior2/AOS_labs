/*
 * =====================================================================================
 *
 *       Filename:  n3.c
 *
 *    Description:  Lab 4, number 3.
 *
 *        Version:  1.0
 *        Created:  24.10.2019 21:32:10
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
        struct packet t;
        int id = 0;
        char buf[100];
        while(1){
            t.value = rand() % 10000;
            t.id = id++;
            if(write(fds[1], &t, sizeof(struct packet)) == -1){
                perror("[P] write error");
            }
            else{
                printf("\n[P] Пакет сгенерирован и отправлен! (ID = %d ; VALUE = %d)\n", t.id, t.value);
            }
        //wait(NULL);
            int n;
            if((n = read(fds_i[0], &buf, 100)) == -1){
                perror("[P] read error!");
            }
            printf("[P] Ответ получен! (ANS = %s)\n", buf);
        }
        printf("[P] Завершение родительского процесса!\n");
        if(close(fds[1]) == -1){
            printf("[P] close fds[1] error");
        }
        if(close(fds_i[0]) == -1){
            printf("[P] close fds_i[0] error");
        }
        wait(NULL);
    }

    else{
        close(fds[1]);
        close(fds_i[0]);
        struct packet rec;
        char buf[100];
        while(1){
            if(read(fds[0], &rec, sizeof(struct packet)) == -1){
                perror("[C] read error");
            }
            else{
                printf("[C] Пакет принят! (ID = %d ; VALUE = %d)\n", rec.id, rec.value);
                printf("[C] Введите ответ на запрос:\n");
                scanf("%s", buf);
                if(write(fds_i[1], &buf, 100) == -1){
                    perror("[C] write error");
                }
                else{
                    printf("[C] Ответ сформирован и отправлен! (ANS = %s)\n", buf);
                }
            }
        }
        printf("[C] Завершение дочернего процесса!\n");

        if(close(fds[0]) == -1){
            perror("[C] close fds[0] error");
        }
        if(close(fds_i[1]) == -1){
            perror("[C] close fds_i[1] error");
        };
            //sleep(100);
    }
}

