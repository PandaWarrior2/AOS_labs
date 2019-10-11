/*
 * =====================================================================================
 *
 *       Filename:  n7.c
 *
 *    Description: Lab 2, number 7
 *
 *        Version:  1.0
 *        Created:  08.10.2019 08:48:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, m19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char * argv[], char * argp[]){

    if(argc < 2){
        printf("Usage: %s program_name [arg1, arg2, ..., argn].\n", *argv);
        exit(1);
    }
    int pid;
    if((pid=fork()) == -1){
        perror("[P] fork error");
        exit(0);
    }

    if(pid){
        printf("[P] Это сообщение выведено из родительского процесса\n");
        printf("[P] fork returned = %d\n", pid);
        printf("[P] Process group = %d\n",getpgrp());
        printf("[P] PID = %d\n",getpid());
        printf("[P] PPID = %d\n",getppid());
        if(pause() == -1){
            perror("");
        }
        printf("[P] Ожидаем завершения дочернего процесса\n");
        int code;
        printf("[P] Дочерний процесс завершён! Статус завершения: %d\n", code);
        int i;
        for(i=0;i<330;i++){
            printf("[P] %d/10\n", i);
            sleep(1);
        }

    }
    else{
        printf("[C] Это сообщение выведено из дочернего процесса\n");
        printf("[C] fork returned = %d\n", pid);
        printf("[C] Process group = %d\n",getpgrp());
        printf("[C] PID = %d\n",getpid());
        printf("[C] PPID = %d\n",getppid());
        if(setpgrp() == -1){
            perror("");
        }
        if(pause() == -1){
            perror("");
        }
        execve(argv[1], argv+1, argp);
        perror("[C] exec error");

    }
    return 0;
}
