/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Lab 6. Top program
 *
 *        Version:  1.0
 *        Created:  01.11.2019 10:42:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
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
#include <signal.h>
#include <sys/wait.h>
static void usage(char*, char*);
int main(int argc, char * argv[]){
    int opt;
    int N = 0;
    int M = 0;
    int L = 0;
    int opts = 0;
    char args[3] = "nml";
    while((opt = getopt(argc, argv, "n:m:l:")) != -1){
        switch(opt){
            case 'n':
                N = strtol(optarg, NULL, 10);
                opts |= (1 << 0);
                break;
            case 'm':
                M = strtol(optarg, NULL, 10);
                opts |= (1 << 1);
                break;
            case 'l':
                L = strtol(optarg, NULL, 10);
                opts |= (1 << 2);
                break;
            default:
                usage(*argv, NULL);
        }
    }

    if(opts < 7){
        fprintf(stderr, "Not found options: ");
        for(int i = 0; i<3; i++){
            if(!(opts & (1<<i))){
                fprintf(stderr, "-%c ", args[i]);
            }
        }
        fprintf(stderr, "\n");
        usage(*argv, NULL);
    }
    int pid;
    if((pid = fork()) == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if(pid){
        waitpid(pid, NULL, 0);
    }
    else{
        printf("[C] Начальный процесс создан! pid = %d. Создаем кольца\n");
        execv("mkring", argv);
        perror("execv");
        exit(EXIT_FAILURE);
    }
    printf("[P] Terminate...\n");
    return 0;
}
static void usage(char * prog_name, char * msg){
    if(msg != NULL){
        fputs(msg, stderr);
    }
    fprintf(stderr, "Usage: %s -n <value> -m <value> -l <value>\n", prog_name);
    exit(EXIT_FAILURE);
}
