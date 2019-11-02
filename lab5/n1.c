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
#include <time.h>
int get_stats(int);
void gen_random(char *, const int);
int main(int argc, char * argv[]){
    int qd;
    key_t key;
    if((key = ftok("queue_file", 1)) == -1){
        perror("ftok");
        exit(1);
    }
    printf("key = %d\n", key);
    if((qd = msgget(key, IPC_CREAT | 0666)) == -1) {
        perror("msgget");
        exit(1);
    }
    struct msqid_ds qds;
    get_stats(qd);
    struct msg {
        long mtype;
        char mtext[20];
    } msg;

    struct {
        long mtype;
        int id;
        char mtext[50];
    } msg1;

    char str[20];
    char str1[50];
    int i;
    for(i = 1; i < 20; i++){
        msg.mtype = (long)i;
        gen_random(str, 20);
        strcpy(msg.mtext, str);
        if(msgsnd(qd, &msg, 20, IPC_NOWAIT) == -1){
            perror("msgsnd");
        }
        msg1.mtype = (long)i*10;
        gen_random(str1, 50);
        strcpy(msg1.mtext,  str);
        if(msgsnd(qd, &msg1, 54, IPC_NOWAIT) == -1){
            perror("msgsnd");
        }
        printf("Ok ");

    }
    printf("\n");
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
    char str_t[100];
    strftime (str_t, 100, "%d.%m.%y %X", localtime(&qds.msg_ctime));
    printf("UserID = %d\n", qds.msg_perm.uid);
    printf("GroupID = %d\n", qds.msg_perm.gid);
    printf("CTime = %d\n", str_t);
    printf("Max bytes = %d\n", qds.msg_qbytes);
    printf("Number of messages: %d\n", qds.msg_qnum);
    return 0;
}

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    int i;
    for (i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}
