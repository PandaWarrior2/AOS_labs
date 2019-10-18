/*
 * =====================================================================================
 *
 *       Filename:  n6.c
 *
 *    Description:  Lab 3, number 6
 *
 *        Version:  1.0
 *        Created:  14.10.2019 18:46:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Svyatoslav Nikitin, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
void handler(int);
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
        if(kill(pid, SIGINT) == -1)
        {
            perror("kill error");
        }
        if(wait(&code) == -1){
            perror("wait error");
        }
        printf("Exit status: %d\n", code);
    }
    else{

        printf("[C] Fork returned %d\n", pid);
        printf("[C] Дочерний процесс создан! PID = %d\n", getpid());
#ifdef NUMBER7
        pause();
#else
        int i,j;
        for(i = 0;i < 100;i++){
            for(j = 0; j < 100 ; j++){
                printf("[C] i = %d\n", i);
            }
        }
#endif
        printf("[C] Процесс завершен! \n");
    }
    return 0;
}
void handler(int sigid){
    printf("Сигнал перехвачен обработчиком!\n");
}
