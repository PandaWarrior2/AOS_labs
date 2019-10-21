/*
 * =====================================================================================
 *
 *       Filename:  n1.c
 *
 *    Description:  Lab 4, number 1
 *
 *        Version:  1.0
 *        Created:  20.10.2019 09:07:11
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
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
        while(1){
            t.value = rand() % 10000;
            t.id = id++;
            if(write(fds[1], &t, sizeof(struct packet)) == -1){
                perror("[P] write error");
            }
            else{
                printf("\n[P] Пакет сгенерирован и отправлен! (ID = %d ; VALUE = %d)\n", t.id, t.value);
            }

            if(read(fds_i[0], &t, sizeof(struct packet)) == -1){
                perror("[P] read error!");
            }
            else{
                printf("[P] Получен ответ на пакет ID = %d. VALUE = %d\n",t.id, t.value);
            }
            if(id == 15) {
                printf("[P] Завершение родительского процесса!\n");
                close(fds[0]);
                close(fds_i[1]);
                wait(&id);
                break;
            }
            sleep(1);
        }

    }
    else{
        close(fds[1]);
        close(fds_i[0]);
        struct packet rec;
        while(1){
            if(read(fds[0], &rec, sizeof(struct packet)) == -1){
                perror("[C] read error");
            }
            else{
                printf("[C] Пакет принят! (ID = %d ; VALUE = %d)\n", rec.id, rec.value);
                rec.value = (rec.value % 255);
                if(write(fds_i[1], &rec, sizeof(struct packet)) == -1){
                    perror("[C] write error");
                }
                else{
                    printf("[C] Ответ сформирован и отправлен! (ID = %d ; VALUE = %d)\n", rec.id, rec.value);
                }
                if(rec.id == 14){
                    printf("[C] Завершение дочернего процесса!\n");
                    close(fds[1]);
                    close(fds_i[0]);
                    break;
                }
            }
        }
    }
}
