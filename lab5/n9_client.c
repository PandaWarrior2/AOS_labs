/*
 * =====================================================================================
 *
 *       Filename:  n6_client_new.c
 *
 *    Description:  Lab 5, number 6. Client.
 *
 *        Version:  2.0
 *        Created:  30.10.2019 14:43:58
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
#include <time.h>
int main(int argc, char * argv[]){
    if(argc < 2) {
        printf("Usage: %s <queue key>\n");
        exit(1);
    }
    printf("Client started!\n");
    int srv_key = atoi(argv[1]);
    int qd, pqd;
    if((pqd = msgget(srv_key, 0755)) == -1){
        perror("msgget (srv queue)");
        exit(1);
    }
    printf("Соедиение с очередью сервера (%d) установлено!\n", srv_key);
    if((qd = msgget(srv_key+1, IPC_CREAT | 0755)) == -1){
        perror("msgget (client queue)");
        exit(1);
    }
    struct {
        long mtype;
        char mtext[20];
    } tx, rx;

    while(1){
        printf("Введите сообщение: ");
        scanf("%s", tx.mtext);
        tx.mtype = getpid();
        if(msgsnd(pqd, &tx, 20, 0) == -1){
            perror("msgsnd");
        }
        else{
            printf("Сообщение отправлено! Ожидание ответа...\n");
        }

        if(msgrcv(qd, &rx, 20, 0, 0) == -1){
            perror("msgrcv");
        }
        else{
            printf("Получен ответ! (key = %d ; text = %s)\n", rx.mtype, rx.mtext);
        }
    }


}
