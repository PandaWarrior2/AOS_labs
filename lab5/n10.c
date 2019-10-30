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
int main(int argc, char * argv[]){
    printf("Server started!\n");
    int qd, cqd;
    if((qd = msgget(getpid(), IPC_CREAT | 0755)) == -1){
        perror("msgget (rx)");
        exit(1);
    }
    else{
        printf("Очередь создана! Ключ: %d\n", getpid());
    }

    printf("Ожидается получение сообщений...\n");
    struct {
        long mtype;
        char mtext[20];
    } rx, tx;

    while(1){
        if(msgrcv(qd, &rx, 20, -1000000, 0) == -1){
            perror("msgrcv");
        }
        else{
            printf("[RECIEVE] Получено сообщение с ключом %ld: %s\n", rx.mtype, rx.mtext);
            tx.mtype = rx.mtype + 1000000;
            sprintf(tx.mtext, "%d", H(rx.mtext));
            if(msgsnd(qd, &tx, 20, 0) == -1){
                perror("msgsnd");
            }
            else{
                printf("[SEND] Ответ отправлен! (key = %ld, text = %s)\n", tx.mtype, tx.mtext);
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
