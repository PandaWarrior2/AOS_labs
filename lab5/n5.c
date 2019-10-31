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
static void usage(char*, char*);
int main(int argc, char * argv[]){
    /*if(argc < 2){
        printf("Usage: %s key\n", argv[0]);
        exit(1);
    }*/
    int mode=0, opt;
    key_t key;
    while((opt = getopt(argc, argv, "f:k:")) != -1){
        switch(opt){
            case 'k':
                key = strtol(optarg, NULL, 10);
                mode = 1;
                break;
            case 'f':
                if((key = ftok(optarg, 1)) == -1){
                    perror("ftok");
                    exit(1);
                }
                mode = 2;
                break;
            default:
                usage(argv[0], "Unreconized option\n");
        }
    }

    if(!mode){
        usage(argv[0], "must use either -f or -k option\n");
    }
    int qid;
    if((qid = msgget(key, 0666)) == -1){
        perror("msgget");
    }
    if(msgctl(qid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(1);
    }
    printf("Queue with key %d deleted!\n", key);
    return 0;
}

static void usage(char * prog_name, char * msg){
    if(msg != NULL){
        fputs(msg, stderr);
    }
    fprintf(stderr, "Usage %s [options]\n", prog_name);
    fprintf(stderr, "Options are:\n");
    fprintf(stderr, "-k     key of queue\n");
    fprintf(stderr, "-f     filename\n");
    exit(EXIT_FAILURE);
}
