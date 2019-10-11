/*
 * =====================================================================================
 *
 *       Filename:  n10.c
 *
 *    Description:  Lab 2, Number 10
 *
 *        Version:  1.0
 *        Created:  09.10.2019 22:10:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, m19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char * argv[], char * argp[]){
    if(argc < 2){
        printf("Usage: %s filename \n", argv[0]);
    }
    else{
        int code = fork();
        if(code == -1){
            perror("fork error");
            exit(1);
        }
        if(code){
            printf("[P] Parent PID = %d\n", getpid());
            printf("[P] Child process created! \n");
        }
        else{
            printf("[C] Child PID = %d\n", getpid());
            execve(argv[1], (argv+1),argp);
        }
    }
}
