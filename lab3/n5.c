/*
 * =====================================================================================
 *
 *       Filename:  n5.c
 *
 *    Description:  Lab 3, number 5
 *
 *        Version:  1.0
 *        Created:  14.10.2019 18:36:17
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
        if(kill(pid, SIGUSR1) == -1)
        {
            perror("kill error");
        }
        if(wait(&code) == -1){
            perror("wait error");
        }
        printf("Exit status: %d\n", code);
    }
    else{
#ifdef NUMBER8
        signal(SIGUSR1, signal_handler);
#endif
        printf("[C] Fork returned %d\n", pid);
        printf("[C] Дочерний процесс создан! PID = %d\n", getpid());
        for(int i = 0;i < 100;i++){
#ifdef NUMBER7
            pause();
#else
            for(int j = 0; j < 10000 ; j++);
#endif
            printf("%d ", i);
        }
    }
    return 0;
}
