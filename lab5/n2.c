/*
 * =====================================================================================
 *
 *       Filename:  n2.c
 *
 *    Description:  Lab 5, number 2
 *
 *        Version:  1.0
 *        Created:  10/28/2019 03:28:24 PM
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
int main(int argc, char * argv[]){
    if(argc < 3){
        printf("Usage: %s queue_file msg_type\n", argv[0]);
        exit(1);
    }
    int msg_type = strtol(argv[2], NULL, 10);
    key_t key;
    if((key = ftok(argv[1], 1)) == -1){
        perror("ftok");
        exit(1);
    }
    int qd;

    struct msg {
        long mtype;
        char mtext[20];
    } msg;

    if((qd = msgget(key, IPC_CREAT | 0755)) == -1) {
        perror("msgget");
        exit(1);
    }

    if(msgrcv(qd, &msg, 20, msg_type, 0) == -1) {
        perror("msgrcv");
    }
    else{
        printf("Message recieved.  mtype = %d, mtext = %s\n", msg.mtype, msg.mtext);
    }
    return 0;
}
