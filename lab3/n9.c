/*
 * =====================================================================================
 *
 *       Filename:  n9.c
 *
 *    Description:  Lab 4, number 9
 *
 *        Version:  1.0
 *        Created:  18.10.2019 23:12:30
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
        signal(SIGINT, handler);
        printf("[C] Fork returned %d\n", pid);
        printf("[C] Дочерний процесс создан! PID = %d\n", getpid());
        for(int i = 0;i < 100;i++){
            pause();
            printf("%d ", i);
        }
        printf("[C] Процесс завершен! \n");
    }
    return 0;
}
void handler(int sigid){
    printf("Сигнал перехвачен обработчиком!\n");
}
