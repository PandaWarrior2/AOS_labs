/*
 * =====================================================================================
 *
 *       Filename:  n6_client.c
 *
 *    Description:  Lab 5, number 6 - CLIENT
 *
 *        Version:  1.0
 *        Created:  29.10.2019 10:55:39
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
#include <time.h>
void gen_random_str(char*, const int);
int main(int argc, char * argv[]){
    printf("[%d] Client started!\n", getpid());
    int pkey = atoi(argv[1]);
    int key = atoi(argv[2]);
    printf("[%d] key = %d ; parent key = %d\n", getpid(), key, pkey);
    int qd;
    int pqd;
    if((qd = msgget(key, IPC_CREAT | 0755)) == -1){
        printf("[ERR %d] msgget: %s", getpid(), sys_errlist[errno]);

        exit(1);
    }
    else{
        printf("[%d] Очередь создана! (%d) \n", getpid(), qd);
    }

    if((pqd = msgget(pkey, 0755)) == -1){
    printf("[ERR %d] msgget: %s", getpid(), sys_errlist[errno]);
        exit(1);
    }
    else{
        printf("[%d] Очередь создана! (%d; %d) \n", getpid(), pkey, qd);
    }
    printf("[%d] Выполняется формирование и отправка сообщений...\n", getpid());

    struct msg {
        long mtype;
        char mtext[20];
    } msg, ans;

    srand((unsigned int)time(NULL) % getpid());

    for(int i = 1; i < 26; i++){
        msg.mtype = getpid();
        gen_random_str(msg.mtext, 19);

        if(msgsnd(pqd, &msg, 20, 0) == -1){
            printf("[ERR %d] msgsnd: %s", getpid(), sys_errlist[errno]);
        }
        else{
            printf("[SEND %d] Сообщение отправлено! -> %d\n", getpid(), pqd);
        }
    }

    for(int i = 0; i < 25; i++){
        if(msgrcv(qd, &ans, 20, 0, 0) == -1) {
            printf("[ERR %d] msgrcv: %s", getpid(), sys_errlist[errno]);
        }
        else{
            printf("[ANS %d] Ответ получен! (%s) \n", getpid(), ans.mtext);
        }

    }
    printf("[%d] Terminated!\n", getpid());
}

void gen_random_str(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}
