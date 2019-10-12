/*
 * =====================================================================================
 *
 *       Filename:  n1.c
 *
 *    Description:  Lab #3, number 1.
 *
 *        Version:  1.0
 *        Created:  11.10.2019 23:01:48
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

void signal_handler(int);

int main(int argc, char * argv[], char * argp[]){
    signal(SIGINT, signal_handler);
    while(1){
        pause();
    }
    return 0;
}

void signal_handler(int signal_id){
    printf("Сигнал процессу перехвачен обработчиком!\n");
    signal(SIGINT, SIG_DFL);
}
