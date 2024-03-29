/*
 * =====================================================================================
 *
 *       Filename:  n10.c
 *
 *    Description:  Lab 3, Number 10
 *
 *        Version:  1.0
 *        Created:  17.10.2019 17:45:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nikitin Svyatoslav, M19-512
 *   Organization:  MEPhI
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
void signal_handler(int);

int main(int argc, char * argv[]) {
     struct sigaction act, oact;
     sigset_t set, oset;

     act.sa_handler = signal_handler;
     if(sigaction(SIGUSR1, &act, &oact) == -1){
        perror("sigaction error");
     }
     if(sigaction(SIGUSR2, &act, &oact) == -1){
        perror("sigaction error");
     }
     if(sigaction(SIGALRM, &act, &oact) == -1){
        perror("sigaction error");
     }
     if(sigaction(SIGCONT, &act, &oact) == -1){
        perror("sigaction error");
     }
     if(sigaction(SIGINT, &act, &oact) == -1){
        perror("sigaction error");
     }
     if(sigfillset(&set) == -1){
        perror("sigemptyset error");
     }
     if(sigdelset(&set, SIGUSR1) == -1){
        perror("sigdelset error");
     }
     sigprocmask(SIG_SETMASK, &set, &oset);
     int pid;
     kill(getpid(), SIGUSR1);
     sigprocmask(SIG_SETMASK,&oset,0);
}

void signal_handler(int sig) {
    printf("Сигнал %d перехвачен!\n", sig);
    if(sig == SIGUSR1) {
        sleep(30);
    }
        printf("\n");

}
