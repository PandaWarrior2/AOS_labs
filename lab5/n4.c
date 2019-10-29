/*
 * =====================================================================================
 *
 *       Filename:  n4.c
 *
 *    Description:  Lab 5, number 4
 *
 *        Version:  1.0
 *        Created:  29.10.2019 07:20:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
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
        printf("Usage: %s queue_id msg_type\n", argv[0]);
        exit(1);
    }
    int msg_type = strtol(argv[2], NULL, 10);
    int qid = strtol(argv[1], NULL, 10);
    int qd;

    struct msg {
        long mtype;
        char mtext[20];
    } msg;

    if((qd = msgget(qid, IPC_CREAT | 0755)) == -1) {
        perror("msgget");
        exit(1);
    }

    if(msgrcv(qd, &msg, 20, msg_type, 0) == -1) {
        perror("msgrcv");
    }
    else{
        printf("Message recieved.  mtype = %ld, mtext = %s\n", msg.mtype, msg.mtext);
    }
    return 0;
}
