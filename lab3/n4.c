/*
 * =====================================================================================
 *
 *       Filename:  n4.c
 *
 *    Description:  Lab 3, number 4.
 *
 *        Version:  1.0
 *        Created:  14.10.2019 18:03:14
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
int main (int argc, char * argv[]) {
    int pid;
    if((pid = fork()) == -1) {
        perror("fork error");
        exit (1);
    }
    if(pid){
        printf("[P] Fork returned %d\n", pid);
        printf("[P] PID = %d\n", getpid());
        int code;
        if(wait(&code) == -1){
            perror("wait error");
        }
        else{
            printf("Exit status: %d\n", code);
        }
    }
    else{

        printf("[C] Fork returned %d\n", pid);
        printf("[C] Дочерний процесс создан! PID = %d\n", getpid());
#ifdef NUMBER7
    struct sigaction act, oact;
    act.sa_handler = signal_handler;
    if (sigaction(SIGALRM, &act, &oact) == -1){
        perror("sigaction error");
    }
        pause();
#endif
        int i,j;
        for(i = 0;i < 100;i++){
            for(j = 0; j < 100 ; j++){
                printf("[C] i = %d\n", i);
            }
        }
    }
    return 0;
}

void signal_handler(int sigid){
    printf("[HND] signal catched by handler!\n");
}
