/*
 * =====================================================================================
 *
 *       Filename:  n5.c
 *
 *    Description: Lab 3, number 5
 *
 *        Version:  1.0
 *        Created:  21.10.2019 08:57:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int pcheck(int, char*);
int main(int argc, char * argv[], char * argp[]){
    int fds[2];
    pcheck(pipe(fds), "pipe error");
    if(pcheck(fork(), "fork1 error") == 0){
        printf("[C-WHO] Дочерний процесс запущен! PID = %d\n", getpid());
        pcheck(close(1),        "[C-WHO] close(1) error)");
        pcheck(close(fds[0]),   "[C-WHO] close(fds[0]) error");
        pcheck(dup2(fds[1], 1), "[C-WHO] dup error");
        execvp("/usr/bin/who", argv);
        perror("[C-WHO] execvp error");
    }

    if(pcheck(fork(), "fork2 error") == 0){
        printf("[C-WC] Дочерний процесс запущен! PID = %d\n", getpid());
        char buf;
        pcheck(close(0),      "[C-WC] close(0) error)");
        pcheck(close(fds[1]), "[C-WC] close(fds[1] error");
        pcheck(dup2(fds[0], 0), "[C-WC] dup2 error");
        char * args[] = {"/usr/bin/wc", "-l", NULL};
        execvp("/usr/bin/wc", args);
        perror("[C-WC] execvp error");
    }
    pcheck(close(fds[0]), "close fds0 error");
    pcheck(close(fds[1]), "close fds1 error");
    return 1;
}

int pcheck(int func, char * message){
    if(func == -1) {
        perror(message);
        exit(1);
    }
    else{
        return func;
    }
}
