/*
 * =====================================================================================
 *
 *       Filename:  n3.c
 *
 *    Description:  Lab 3, number 3
 *
 *        Version:  1.0
 *        Created:  12.10.2019 15:43:02
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
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void signal_handler(int);
int main(int argc, char * argv[], char * argp[]){
    if(argc < 2){
        printf("Usage: %s program_name [arg1, arg2, ..., argn].\n", *argv);
        exit(1);
    }
    signal(SIGCHLD, signal_handler);
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
        printf("[P] Ожидаем завершения дочернего процесса\n");
        while(1){
        }
    }
    else{
        printf("[C] Это сообщение выведено из дочернего процесса\n");
        printf("[C] fork returned = %d\n", pid);
        printf("[C] Process group = %d\n",getpgrp());
        printf("[C] PID = %d\n",getpid());
        printf("[C] PPID = %d\n",getppid());
        execve(argv[1], argv+1, argp);
        perror("[C] exec error");

    }
    return 0;
}
void signal_handler(int signal_id){
    printf("Сигнал процессу перехвачен обработчиком! %d\n", getpid());
    int w, n;
    if((w = wait(&n)) == -1){
        perror("wait error");
    }
    else{
        printf("PID %d: Exit code = %d\n", w, n);
    }
}
