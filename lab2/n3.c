/*
 * =====================================================================================
 *
 *       Filename:  n3.c
 *
 *    Description:  Lab #2, Number 3
 *
 *
 *        Version:  1.0
 *        Created:  06.10.2019 10:01:48
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

int main(int argc, char * argv[]){
    int pid = fork();
    char * args[] = {"/bin/ls", "-la", NULL};

    if(pid == -1){
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
        int code;
        if(wait(&code) == -1) {
            perror("[P] wait error");
        }
        else{
            printf("[P] Дочерний процесс завершён! Статус завершения: %d\n", code);
        }

    }
    else{
        printf("[C] Это сообщение выведено из дочернего процесса\n");
        printf("[C] fork returned = %d\n", pid);
        printf("[C] Process group = %d\n",getpgrp());
        printf("[C] PID = %d\n",getpid());
        printf("[C] PPID = %d\n",getppid());
        int code;
        if((code=execvp(args[0], args)) == -1){
            perror("[C] exec error");
        }

    }
    return 0;
}
