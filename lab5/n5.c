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
    if(argc < 2){
        printf("Usage: %s queue_id\n", argv[0]);
        exit(1);
    }

    int qid =  strtol(argv[1], NULL, 10);
    if(msgctl(qid, IPC_RMID, 0) == -1){
        perror("");
        exit(1);
    }
    printf("Queue %d deleted!\n", qid);
    return 0;
}
