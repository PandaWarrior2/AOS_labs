/*
 * =====================================================================================
 *
 *       Filename:  n7.c
 *
 *    Description:  Lab 3, number 7
 *
 *        Version:  1.0
 *        Created:  14.10.2019 18:48:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, m19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#define _POSIX_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void signal_handler(int);
int main (int argc, char * argv[]) {
    int pid;
    if((pid = fork()) == -1) {
        perror("fork error");
        exit (1);
    }
    struct sigaction act, oact;
    act.sa_handler = signal_handler;
    if (sigaction(SIGINT, &act, &oact) == -1){
        perror("sigaction error");
    }

    if(pid){
        printf("[P] Fork returned %d\n", pid);
        printf("[P] PID = %d\n", getpid());
        int code;
        if(wait(&code) == -1){
            perror("wait error");
        }
        printf("Exit status: %d\n", code);
    }
    else{

        printf("[C] Fork returned %d\n", pid);
        printf("[C] Дочерний процесс создан! PID = %d\n", getpid());
        int i,j;
        for(i = 0;i < 100;i++){
            if(pause() == -1){
                perror("pause error");
            }
            printf("[C] i = %d\n", i);
        }
        printf("[C] Done!\n");
    }
    return 0;
}

void signal_handler(int sig_id){
    printf("Signal is handled! \n");
}
