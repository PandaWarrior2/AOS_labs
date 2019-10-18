/*
 * =====================================================================================
 *
 *       Filename:  n11.c
 *
 *    Description:  Lab 3, number 11
 *
 *        Version:  1.0
 *        Created:  16.10.2019 07:44:28
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
#include <fcntl.h>
#include <errno.h>
void signal_handler(int);
int main(int argc, char * argv []){
    if(argc < 2){
        printf("Usage: %s dimension\n", argv[0]);
    }
    int dim = atoi(argv[1]);
    int fd;
    if((fd = open("matrix", O_RDWR | O_CREAT, 0755)) == -1) {
        perror("Open error (matrix)");
        exit(1);
    }
    printf("File 'matrix' opened! \n");
    int i;
    char * str;
    str = malloc(dim);
    for(i=0;i<dim;i++){
        *(str+i) = '0';
    }
    for(i=0;i<dim; i++){
        write(fd, str, dim);
    }

    int pid;
    if((pid = fork()) == -1){
        perror("fork error (pid_out)");
        exit(2);
    }

    struct sigaction act, oact;
    act.sa_handler = signal_handler;
    sigset_t newset, oset;
    sigaddset(&newset, SIGUSR1);
    sigaddset(&newset, SIGINT);
    if (sigaction(SIGUSR1, &act, &oact) == -1){
        perror("sigaction error");
    }
    sigprocmask(SIG_UNBLOCK, &newset, &oset);
    if(pid){
        sigaction(SIGUSR1, &act, &oact);
        printf("[P] Дочерний процесс создан (PID = %d)\n", pid);
        printf("[P] Родительский процесс (PID = %d) отвечает за отрисовку матрицы на экране \n", getpid());
        int n;
        while (1){
            //sigwait(&newset, &n);
            //sigsuspend(&newset);
           // sleep(1);
            printf("[P] Результат обработки:\n");

            lseek(fd, 0, SEEK_SET);
            for(int i=0;i<dim;i++){
                read(fd, str, 10);
                write(1, str, 10);
                write(1, "\n", 1);
            }
            kill(pid, SIGUSR1);
            sigwait(&newset, &n);
            //sigsuspend(&newset);
        }
    }
    else {
        sigaction(SIGUSR1, &act, &oact);
        printf("[C] Дочерний процесс (PID = %d) отвечает за проставление 1 в первом ненулевом элементе главной диагонали. \n", getpid());
        int i=0,n;
        char s;
        while(1){
            //printf("[C] Обработка матрицы...");
            sigwait(&newset, &n);
            lseek(fd, 0, SEEK_SET);
            do{
                printf(" ");
                n = read(fd, &s, 1);
                if(s == '0') {
                    lseek(fd, (long)-1, SEEK_CUR);
                    write(fd, "1", 1);
                    break;
                }
                lseek(fd, 10, SEEK_CUR);
            }while(n == 1);
            //kill(getppid(), SIGUSR1);
            if(i == dim)
            {
                kill(getppid(), SIGINT);
                break;
            }
            else{
                kill(getppid(), SIGUSR1);
                i++;
            }
        }
    }
    return 0;
}

void signal_handler(int sigid){
    if(sigid == SIGUSR1){
        printf("\n");
        sleep(1);
    }
}
