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
#include <mqueue.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char * argv[]){
    int qd;
    struct mq_attr attr;
    if((qd = mq_open("/queue", O_RDWR | O_CREAT, 0755, NULL)) == -1){
        perror("mq_open");
        exit(1);
    }
    if(mq_getattr(qd, &attr) == -1){
        perror("mq_getattr");
        exit(1);
    }
    printf("Message queue stats:\n");
    printf("Flags: %d\nMax messages: %d\nMax message size: %d\nMessages count: %d\n", attr.mq_flags, attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    return 0;
}

