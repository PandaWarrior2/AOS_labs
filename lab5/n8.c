/*
 * =====================================================================================
 *
 *       Filename:  n6new.c
 *
 *    Description:  Lab 5, number 6.
 *
 *        Version:  2.0
 *        Created:  30.10.2019 14:27:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, M19-512
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
#include <signal.h>
#include <sys/wait.h>
int H(char*);
void signal_handler(int);
int main(int argc, char * argv[]){
    printf("Server started!\n");
    int qd;
    if((qd = msgget(getpid(), IPC_CREAT | 0755)) == -1){
        perror("msgget");
        exit(1);
    }
    else{
        printf("Очередь создана! Ключ: %d\n", getpid());
    }
    struct sigaction act, oact;
    act.sa_handler = signal_handler;
    act.sa_flags = SA_RESETHAND;
    if(sigaction(SIGINT, &act, &oact) == -1){
        perror("sigaction");
    }
    printf("Ожидается получение сообщений...\n");
    struct {
        long mtype;
        char mtext[20];
    } rx, tx;

    while(1){
        if(msgrcv(qd, &rx, 20, 0, 0) == -1){
            //perror("msgrcv");
        }
        else{
            printf("[RECIEVE] Получено сообщение с ключом %d: %s\n", rx.mtype, rx.mtext);
        }
        int cqd;
        if((cqd = msgget(rx.mtype, 0755)) == -1){
            //perror("msgget (client queue)");
        }
        else{
            tx.mtype = 1;
            sprintf(tx.mtext, "%d", H(rx.mtext));
            if(msgsnd(cqd, &tx, 20, 0) == -1){
                perror("msgsnd");
            }
            else{
                printf("[SEND] Ответ отправлен! (key = %d, text = %s)\n", tx.mtype, tx.mtext);
            }
        }
    }
}

int H(char * str){
    int result = 0;
    int i = 0;
    do{
        result ^= *(str+i);
    } while(*(str+(++i)));
    return result;
}

void signal_handler(int sig){
    if(sig == SIGINT){
        int qd;
        if((qd = msgget(getpid(), 0755)) == -1){
            perror("[HND] msgget");
        }
        else{
            if(msgctl(qd, IPC_RMID, NULL) == -1){
                perror("[HND] msgctl");
            }
            else{
                printf("[HND] Очередь %d уничтожена!\n", getpid());
                exit(0);
            }
        }
    }
}
