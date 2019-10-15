/*
 * =====================================================================================
 *
 *       Filename:  n6.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14.10.2019 18:46:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
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
        if(kill(pid, SIGINT) == -1)
        {
            perror("kill error");
            exit(2);
        }
        if(wait(&code) == -1){
            perror("wait error");
            exit(3);
        }
        printf("Exit status: %d\n", code);
    }
    else{

        printf("[C] Fork returned %d\n", pid);
        printf("[C] Дочерний процесс создан! PID = %d\n", getpid());
        int i,j;
        for(i = 0;i < 100;i++){
            for(j = 0; j < 100 ; j++){
                printf(" i = %d\n", i);
            }
        }
    }
    return 0;
}
