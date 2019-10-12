/*
 * =====================================================================================
 *
 *       Filename:  n2.c
 *
 *    Description:  Lab 3, number 2
 *
 *        Version:  1.0
 *        Created:  12.10.2019 15:26:40
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

int main(int argc, char * argv[], char * argp[]) {
    struct sigaction act, old_act;
    act.sa_handler = signal_handler;
    act.sa_flags = 0;
    sigaction(SIGINT, &act, &old_act);
    while(1){
        pause();
    }
    return 0;

}
void signal_handler(int signal_id){
    printf("Сигнал процессу перехвачен обработчиком!\n");
    signal(SIGINT, SIG_DFL);
}
