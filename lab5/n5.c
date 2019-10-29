/*
 * =====================================================================================
 *
 *       Filename:  n5.c
 *
 *    Description:  Lab 5, number 5.
 *
 *        Version:  1.0
 *        Created:  29.10.2019 07:26:45
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
    if(argc < 2){
        printf("Usage: %s key\n", argv[0]);
        exit(1);
    }

    int key =  strtol(argv[1], NULL, 10);
    int qid;
    if((qid = msgget(key, 0755)) == -1){
        perror("msgget");
    }
    if(msgctl(qid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(1);
    }
    printf("Queue with key %d deleted!\n", key);
    return 0;
}
