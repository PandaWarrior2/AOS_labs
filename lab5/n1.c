/*
 * =====================================================================================
 *
 *       Filename:  n1.c
 *
 *    Description:  Lab 5, number 1
 *
 *        Version:  1.0
 *        Created:  27.10.2019 13:16:57
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
int get_stats(int);
void gen_random(char *, const int);
int main(int argc, char * argv[]){
    int qd;
    if((qd = msgget(1, IPC_CREAT | 0755)) == -1) {
        perror("msgget");
        exit(1);
    }
    struct msqid_ds qds;
    get_stats(qd);
    struct msg {
        long mtype;
        char mtext[20];
    } msg;

    char str[20];
    for(int i = 0; i < 50; i++){
        msg.mtype = (long)i;
        gen_random(str, 10);
        strcpy(msg.mtext, str);
        if(msgsnd(qd, &msg, 20, 0) == -1){
            perror("msgsnd");
        }
        printf("Message send! \n");
    }
    get_stats(qd);
    //it's number 2
    /*printf("Recieve messages...\n");
    for(int i = 0; i < 20; i++) {
        if(msgrcv(qd, &msg, 20, 0, IPC_NOWAIT) == -1) {
            perror("msgrcv");
        }
        else{
            printf("Message recieved.  mtype = %d, mtext = %s\n", msg.mtype, msg.mtext);
        }
    }
    */
    return 0;
}

int get_stats(int qd){
    struct msqid_ds qds;
    if(msgctl(qd, IPC_STAT, &qds) == -1){
        perror("msgctl");
        return -1;
    }
    printf("UserID = %d\n", qds.msg_perm.uid);
    printf("GroupID = %d\n", qds.msg_perm.gid);
    printf("CTime = %d\n", qds.msg_ctime);
    printf("Max bytes = %d\n", qds.msg_qbytes);
    printf("Number of messages: %d\n", qds.msg_qnum);
    return 0;
}

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}
