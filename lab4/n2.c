/*
 * =====================================================================================
 *
 *       Filename:  n2.c
 *
 *    Description:  Lab 4, number 2
 *
 *        Version:  1.0
 *        Created:  20.10.2019 14:50:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, m19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
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
        int n;
        char c;
        while(1){
            t.value = rand() % 10000;
            t.id = id++;
            if(write(fds[1], &t, sizeof(struct packet)) == -1){
                perror("[P] write error");
            }
            else{
                printf("\n[P] Пакет сгенерирован и отправлен! (ID = %d ; VALUE = %d)\n", t.id, t.value);
            }

            printf("Получение ответа...\n");
            do{
                if((n = read(fds_i[0], &c, 1)) == -1){
                    perror("[P] read error!");
                    break;
                }
                else{
                    if(write(1, &c, 1) == -1){
                        perror("[P] write error");
                    }
                }
            } while(n == 1);
            printf("\n[P] Получение ответа завершено!\n");
            if(id == 15) {
                printf("[P] Завершение родительского процесса!\n");
                close(fds[0]);
                close(fds_i[1]);
                break;
            }
            sleep(1);
        }

    }
    else{
        close(fds[1]);
        close(fds_i[0]);
        struct packet rec;
        char buf [100];
        int n;
        while(1){
            if(read(fds[0], &rec, sizeof(struct packet)) == -1){
                perror("[C] read error");
            }
            else{
                printf("[C] Пакет принят! (ID = %d ; VALUE = %d)\n", rec.id, rec.value);
                rec.value = (rec.value % 255);
                printf("Введите ответное сообщение на пакет:\n");
                scanf("%s", buf);
                if((n = write(fds_i[1], buf, strlen(buf))) == -1){
                    perror("[C] write error");
                }
                else{
                    printf("[C] Ответ сформирован и отправлен! (%d bytes)\n", n);
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
